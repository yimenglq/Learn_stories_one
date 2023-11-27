// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/YAction.h"
#include <Action/ActionActorComp.h>
#include <Net/UnrealNetwork.h>

void UYAction::StartAction_Implementation(AActor* IncitingActor)
{
	
	if (IsRuning())
			return;
	UE_LOG(LogTemp, Log, TEXT("UYAction::StartAction_Implementation"), *GetNameSafe(this));
	

	
	UActionActorComp* comp = GetActionActorComp();
	if(comp->GetOwnerRole() == ENetRole::ROLE_Authority)
		StartTime = GetWorld()->TimeSeconds;

	comp->ActiveGameplayTags.AppendTags(GrantsTags);
	bIsRuning = true;
	OnActionStarted.Broadcast(GetActionActorComp(), this);
	if (comp->GetOwner()->HasAuthority())
	{
		if (RepParm.IncitingActor != IncitingActor)
			RepParm.IncitingActor = IncitingActor;
		RepParm.bIsRuningServer = true;
	}
}

void UYAction::StopAction_Implementation(AActor* IncitingActor)
{
	
	UE_LOG(LogTemp, Log, TEXT("UYAction::StopAction_Implementation"), *GetNameSafe(this));
	/*ensureAlways(bIsRuning);*/
	if (!IsRuning())
		return;
	
	UActionActorComp* comp = GetActionActorComp();
	if (comp->GetOwnerRole() == ENetRole::ROLE_Authority)
		StartTime = 0.0f;
	comp->ActiveGameplayTags.RemoveTags(GrantsTags);
	bIsRuning = false;
	OnActionStoped.Broadcast(GetActionActorComp(), this);
	//·þÎñÆ÷
	if (comp->GetOwner()->HasAuthority())
	{
		if (RepParm.IncitingActor != IncitingActor)
			RepParm.IncitingActor = IncitingActor;
		RepParm.bIsRuningServer = false;
	}
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
	if (auto* actor = Cast<AActor>(GetOuter()))
	{
		UActionActorComp* comp =	Cast<UActionActorComp>( actor->GetComponentByClass(UActionActorComp::StaticClass()) );
		if (comp)
		{
			return comp;
		}

	}
	
	return	Cast<UActionActorComp>(GetOuter());
	

}



bool UYAction::IsRuning() const
{

	return bIsRuning;
}



UWorld* UYAction::GetWorld() const
{
		auto*  ActionWorld = Cast<UActorComponent>(GetOuter());
	if(ActionWorld)
	{
		return	ActionWorld->GetWorld();
	}
	else if (auto* ActionWorld2 = Cast<AActor>(GetOuter()))
	{
		return ActionWorld2->GetWorld();
	}
	else
	{
		return nullptr;
	}


	
}




void UYAction::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UYAction,StartTime);
	DOREPLIFETIME(UYAction, RepParm);
	//DOREPLIFETIME_CONDITION(UYAction, RepParm, );
}

void UYAction::OnRep_IsRuning()
{
	if (RepParm.bIsRuningServer)
	{
		StartAction(RepParm.IncitingActor);
	}
	else
	{
		StopAction(RepParm.IncitingActor);
	}


}