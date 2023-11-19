// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/ActionActorComp.h"
#include"Action/YAction.h"
#include <Character_Y.h>
#include <Action/ActionRogueLink.h>
#include <Net/UnrealNetwork.h>
#include"Engine\ActorChannel.h"

// Sets default values for this component's properties
UActionActorComp::UActionActorComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
	// ...
}


// Called when the game starts
void UActionActorComp::BeginPlay()
{
	Super::BeginPlay();
	
	//服务器运行
	if (GetOwner()->HasAuthority())
	{
			for (auto ActionClass : c_ActionsClasses)
				{
					AddAction(GetOwner(), ActionClass);
				
				}
	}
	
	// ...
	
}


// Called every frame
void UActionActorComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	/*FString DeBugMessage =FString::Printf(TEXT("%p"), GetOwner())+":" + GetNameSafe(GetOwner()) + ":" + this->ActiveGameplayTags.ToStringSimple()+ FString::Printf(TEXT("  controller:  %p"), Cast<ACharacter_Y>( GetOwner())->GetController() ) \
		+ FString::Printf(TEXT("  APlayerController:  %p"), Cast<ACharacter_Y>(GetOwner())->GetController<APlayerController>());
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White,DeBugMessage );*/
	//if(GetOwner()->HasAuthority())
	for (auto* Action : c_Actions)
	{
		if (Action)
		{

		
			FColor Color = Action->IsRuning() ? FColor::Red :FColor::White;
		
			FString Msg = FString::Printf(TEXT("[%s] = [%p] : Action: %s , IsRuning: %s , Outer: %s = %p"),
				*GetNameSafe(GetOwner()),
				GetOwner(),
				*Action->ActionName.ToString(),
				(Action->IsRuning() ? TEXT("true") : TEXT("false")),
				*GetNameSafe(Action->GetOuter()),
				Action->GetOuter()
			);
		
			LogOnScreen(GetOwner(),Msg,Color,0.0f);
		}
	}
	

	
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
			//客户端调用
			if (!GetOwner()->HasAuthority())
			{
				ServerStartAction(IncitingActor, InActionName);
			}
			else
			{
				action->StartAction(IncitingActor);
			}
				//action->StartAction(IncitingActor);
			
			
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
			if (GetOwnerRole() != ENetRole::ROLE_Authority)
			{
				ServerStopAction(IncitingActor, InActionName);
			}
			else
			{
				action->StopAction(IncitingActor);
			}
			
				
			
			
			bRet = true;
		}

	}
	return bRet;
}

void UActionActorComp::ServerStartAction_Implementation(AActor* IncitingActor, FName const InActionName)
{
	
		
	StartAction(IncitingActor, InActionName);


	
}
void UActionActorComp::ServerStopAction_Implementation(AActor* IncitingActor, FName const InActionName)
{


	StopAction(IncitingActor, InActionName);



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

bool UActionActorComp::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool ret = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	if(GetOwner()->HasAuthority())
	for (UYAction* action : c_Actions)
	{
		if (action)
		{
			ret |= Channel->ReplicateSubobject(action, *Bunch, *RepFlags);
			
		}
			//ret |= Channel->ReplicateSubobject(c_Actionsc, *Bunch, *RepFlags);
	}

		return ret;
}




void UActionActorComp::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	//复制变量函数 
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UActionActorComp, c_Actions);//复制变量 
	
}
