// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/YAction.h"

void UYAction::StartAction_Implementation(AActor* IncitingActor)
{
	UE_LOG(LogTemp, Log, TEXT("UYAction::StartAction_Implementation"), *GetNameSafe(this));
}

void UYAction::StopAction_Implementation(AActor* IncitingActor)
{
	UE_LOG(LogTemp, Log, TEXT("UYAction::StopAction_Implementation"), *GetNameSafe(this));
}

UWorld* UYAction::GetWorld()
{
		auto*  ActionWorld = Cast<UActorComponent>(GetOuter());
	if(ActionWorld)
	{
		return	ActionWorld->GetWorld();
	}
	else
	{
		return nullptr;
	}


	
}
