// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/YGameModeBase.h"
#include <EnvironmentQuery/EnvQueryManager.h>
#include <Kismet/GameplayStatics.h>
#include"SaveGame\YSaveGameBase.h"
#include"GameFramework\GameStateBase.h"
#include <PlayerState/YPlayerState.h>
#include <EngineUtils.h>
#include <Interactive_Interface.h>
#include <Serialization/ObjectAndNameAsStringProxyArchive.h>


static TAutoConsoleVariable<bool> ConsoleVariable(TEXT("su.Spawn"), true, TEXT("spawn , Timer"), ECVF_Cheat);//控制台变量定义

AYGameModeBase::AYGameModeBase():Super()
{
	/*bNetLoadOnClient = false;
	bPauseable = true;
	bStartPlayersAsSpectators = false;*/

	c_TimeRate = 2.0f;
	c_ActorNum = 0;
	c_ActorRebirthTime = 30.0f;


}

void AYGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	LoadSaveGame();
}



void AYGameModeBase::StartPlay()
{
	Super::StartPlay();
	
	GetWorldTimerManager().SetTimer(c_TimerHandle,this,&AYGameModeBase::SpawnInit,c_TimeRate,true,5.0f);
	

}

void AYGameModeBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AYGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

		AYPlayerState* PlayerState = Cast< AYPlayerState>(NewPlayer);
		if (PlayerState)
		{
			PlayerState->LoadPlayerState(SaveGameObj);
		}

}






void AYGameModeBase::SpawnInit()
{
	if (!ConsoleVariable.GetValueOnGameThread())//控制台变量获取
	{
		return;
	}
	if (ensure(	c_QueryTemp))
	{
		
	
	if (c_ActorNum >= ( ensure(c_CurveFloat)? c_CurveFloat->GetFloatValue(GetWorld()->GetTimeSeconds()): 10)  )
	{
		return;
	}

		
		UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, c_QueryTemp, this,
			EEnvQueryRunMode::RandomBest25Pct, nullptr);
		if (QueryInstance)
		{

			QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &AYGameModeBase::OnQueryFinished);//查询完成后调用事件
		}
	}
}






void AYGameModeBase::OnQueryFinished(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp,Warning,TEXT("Spawn EQS Finished "));
		return;
	}
	TArray<FVector> RetLocations =	QueryInstance->GetResultsAsLocations();//获得EQS位置信息

	if (RetLocations.Num() > 0)
	{
		AActor* SpawnAi = GetWorld()->SpawnActor<AActor>(c_AI_NPC, RetLocations[0], FRotator::ZeroRotator);
		if (SpawnAi)
		{
			SpawnAi->OnDestroyed.AddUniqueDynamic(this, &AYGameModeBase::OnDestroyedSpawnFun);
			c_ActorNum++;
		}
		
	}
}
void AYGameModeBase::OnDestroyedSpawnFun(AActor* DestroyedActor)
{
	c_ActorNum--;
}



void AYGameModeBase::RebirthRules(APlayerController* RebirthActorPlayerController)
{
	

	if (RebirthActorPlayerController)
	{

		

		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelegate;	
		

		TimerDelegate.BindLambda([this](APlayerController* RebirthActorPlayerController)->void
			{
					RebirthActorPlayerController->UnPossess();//解除控制器的Pawn
		
					AActor* StartLoc =	FindPlayerStart(RebirthActorPlayerController);
					RestartPlayerAtPlayerStart(RebirthActorPlayerController, StartLoc);

			}, RebirthActorPlayerController);

		GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, c_ActorRebirthTime,false);
	}
	
}

void AYGameModeBase::AddControllerAttWidget(APlayerController* InPlayerControllerKey, UUserWidget* InWidgetVal)
{
	/*if (UUserWidget** t = c_ControllerAttWidgetMap.Find(InPlayerControllerKey))
	{
		c_ControllerAttWidgetMap.Add(InPlayerControllerKey, InWidgetVal);
	}*/
	c_ControllerAttWidgetMap.Add(InPlayerControllerKey, InWidgetVal);
}

UUserWidget* AYGameModeBase::IsControllerAttWidget(APlayerController* InPlayerControllerKey)
{
	UUserWidget** ret = nullptr;

	ret = c_ControllerAttWidgetMap.Find(InPlayerControllerKey);

	return (ret != nullptr ? *ret: nullptr);
}




void AYGameModeBase::WriteSaveGame()
{
	SaveGameObj->SaveDates.Empty();
	for (int i = 0; i < GameState->PlayerArray.Num(); i++)
	{
		AYPlayerState* PlayerState = Cast< AYPlayerState>(  GameState->PlayerArray[i]);
		if (PlayerState)
		{
			PlayerState->SavePlayerState(SaveGameObj);
		}

	}

	for  (FActorIterator It(GetWorld());It ; ++It )
	{
		AActor* Actor = *It;
		if (!Actor->Implements<UInteractive_Interface>())
		{
			continue;
		}


		FSaveDate Date;
		Date.Name = Actor->GetName();
		Date.Transform = Actor->GetActorTransform();
		

		FMemoryWriter MemWriter(Date.ByteDate);
		FObjectAndNameAsStringProxyArchive Ar(MemWriter, true);
		Ar.ArIsSaveGame = true;

		Actor->Serialize(Ar);

		SaveGameObj->SaveDates.Add(Date);



	}


	UGameplayStatics::SaveGameToSlot(SaveGameObj, FileName, 0);

}

void AYGameModeBase::LoadSaveGame()
{
	if (UGameplayStatics::DoesSaveGameExist(FileName, 0))
	{
		SaveGameObj =  Cast<UYSaveGameBase>	(UGameplayStatics::LoadGameFromSlot(FileName, 0));
		if (SaveGameObj == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("erro Load SaveGame Data."));
			return;
		}
		
		UE_LOG(LogTemp, Log, TEXT("Loaded SaveGame Data."));
		
		for (FActorIterator It(GetWorld()); It; ++It)
		{
			AActor* Actor = *It;
			if (!Actor->Implements<UInteractive_Interface>())
			{
				continue;
			}
			for (auto LoadDate : SaveGameObj->SaveDates )
			{
				if (LoadDate.Name == Actor->GetName())
				{
					Actor->SetActorTransform(LoadDate.Transform);



					FMemoryReader MemReader(LoadDate.ByteDate);
					FObjectAndNameAsStringProxyArchive Ar(MemReader, true);
					Ar.ArIsSaveGame = true;

					Actor->Serialize(Ar);

					break;
				}


			}

			

		}

	
	}
	else
	{
		SaveGameObj = Cast<UYSaveGameBase> (UGameplayStatics::CreateSaveGameObject( UYSaveGameBase::StaticClass() ));
		UE_LOG(LogTemp, Log, TEXT("Created New SaveGame Data."));
	}
}
