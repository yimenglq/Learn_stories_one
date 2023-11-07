// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/YGameModeBase.h"
#include <EnvironmentQuery/EnvQueryManager.h>



static TAutoConsoleVariable<bool> ConsoleVariable(TEXT("su.Spawn"), true, TEXT("spawn , Timer"), ECVF_Cheat);//控制台变量定义

AYGameModeBase::AYGameModeBase()
{
	c_TimeRate = 2.0f;
	c_ActorNum = 0;
	c_ActorRebirthTime = 30.0f;

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
