// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/ActionActorComp.h"
#include"Action/YAction.h"

// Sets default values for this component's properties
UActionActorComp::UActionActorComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActionActorComp::BeginPlay()
{
	Super::BeginPlay();

	for (auto ActionClass : c_ActionsClasses)
	{
		AddAction(GetOwner(), ActionClass);
	}
	// ...
	
}


// Called every frame
void UActionActorComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	FString DeBugMessage = GetNameSafe(GetOwner()) + ":" + this->ActiveGameplayTags.ToStringSimple();
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White,DeBugMessage );
}

void UActionActorComp::AddAction(AActor* IncitingActor,TSubclassOf<UYAction> InActionClss)
{
	if (!ensure(InActionClss))
	{
		return;
	}
	UYAction* NewAction	= NewObject<UYAction>(this, InActionClss);
	if (NewAction)
	{
		c_Actions.Add(NewAction);
		if (NewAction->bStart_Adter_Load)
		{
			if(IncitingActor!=nullptr)
				NewAction->StartAction(IncitingActor);

		}
	}


}

void UActionActorComp::RemvoeAction(FName const InActionName)
{
	for (UYAction* action : c_Actions )
	{
		if (action->ActionName == InActionName)
		{

			c_Actions.Remove(action);
		}

	}
}

bool UActionActorComp::StartAction(AActor* IncitingActor, FName const InActionName)
{
	bool bRet = false;
	for (UYAction* action : c_Actions)
	{
		if (action->ActionName == InActionName)
		{
			if ( !action->IsCanStart(IncitingActor))
			{
				continue;
			}
			action->StartAction(IncitingActor);
			bRet = true;
		}

	}

	return bRet;
}

bool UActionActorComp::StopAction(AActor* IncitingActor, FName const InActionName)
{
	bool bRet = false;
	for (UYAction* action : c_Actions)
	{
		if (action->ActionName == InActionName)
		{
			if (!action->IsRuning())
				continue;
			action->StopAction(IncitingActor);
			bRet = true;
		}

	}
	return bRet;
}

UYAction* UActionActorComp::FindAction(FName const InActionName)
{
	for (UYAction* action : c_Actions)
	{
		if (action->ActionName == InActionName)
		{

			return 	action;
		}
	}
	return nullptr;
}

