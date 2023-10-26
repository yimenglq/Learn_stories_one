// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/YGameModeBase.h"
#include <EnvironmentQuery/EnvQueryManager.h>



AYGameModeBase::AYGameModeBase()
{
	c_TimeRate = 2.0f;
	c_ActorNum = 0;
}

void AYGameModeBase::StartPlay()
{
	Super::StartPlay();
	
	GetWorldTimerManager().SetTimer(c_TimerHandle,this,&AYGameModeBase::SpawnInit,c_TimeRate,true,5.0f);


}

void AYGameModeBase::SpawnInit()
{
	if (ensure(	c_QueryTemp))
	{
	const int ConstActorNum = 10;
	
	if (c_ActorNum >= ConstActorNum)
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
		GetWorld()->SpawnActor<AActor>(c_AI_NPC, RetLocations[0], FRotator::ZeroRotator);
		c_ActorNum++;
	}
}