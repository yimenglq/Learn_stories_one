// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/YAction.h"
#include <Action/ActionActorComp.h>

void UYAction::StartAction_Implementation(AActor* IncitingActor)
{
	if (IsRuning())
			return;
	UE_LOG(LogTemp, Log, TEXT("UYAction::StartAction_Implementation"), *GetNameSafe(this));
	UActionActorComp* comp = GetActionActorComp();
	comp->ActiveGameplayTags.AppendTags(GrantsTags);
	bIsRuning = true;
}

void UYAction::StopAction_Implementation(AActor* IncitingActor)
{
	UE_LOG(LogTemp, Log, TEXT("UYAction::StopAction_Implementation"), *GetNameSafe(this));
	ensureAlways(bIsRuning);

	UActionActorComp* comp = GetActionActorComp();
	comp->ActiveGameplayTags.RemoveTags(GrantsTags);
	bIsRuning = false;
}

bool UYAction::IsCanStart_Implementation(AActor* IncitingActor)
{

	UActionActorComp* comp = GetActionActorComp();
	if (comp->ActiveGameplayTags.HasAny(BlokTags))
	{	
		return false;

	}
	return true;;
}

UActionActorComp* UYAction::GetActionActorComp() const
{
	return Cast<UActionActorComp>(GetOuter());
}



bool UYAction::IsRuning() const
{

	return bIsRuning;
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
