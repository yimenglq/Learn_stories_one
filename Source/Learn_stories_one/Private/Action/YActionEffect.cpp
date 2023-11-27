// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/YActionEffect.h"
#include"Action\ActionActorComp.h"
#include"GameFramework\GameStateBase.h"

void UYActionEffect::StartAction_Implementation(AActor* IncitingActor)
{
	Super::StartAction_Implementation(IncitingActor);
		UActionActorComp* comp = GetActionActorComp();
		if (comp)
		{
			FTimerDelegate TimerDelegate;
			//间隔时间
			TimerDelegate.BindUFunction(this, "Effect", IncitingActor);
			GetWorld()->GetTimerManager().SetTimer(TH_Spaced, TimerDelegate, Spaced, true);
		/*
			if (comp->GetOwnerRole() != ENetRole::ROLE_Authority)
			{
				return;
			}*/
			TimerDelegate.Unbind();
			//持续时间一到 调用停止动作
			TimerDelegate.BindUFunction(this, "StopAction", IncitingActor);
			GetWorld()->GetTimerManager().SetTimer(TH_Persistent, TimerDelegate, Persistent, false);
		}

}

void UYActionEffect::StopAction_Implementation(AActor* IncitingActor)
{
	if (GetWorld()->GetTimerManager().GetTimerRemaining(TH_Spaced) < Spaced / 2.0)
	{
		this->Effect(IncitingActor);
	}

	Super::StopAction_Implementation(IncitingActor);

	if (UActionActorComp* ActionComp = Cast<UActionActorComp>(IncitingActor->GetComponentByClass(UActionActorComp::StaticClass()) ) )
	{
		ActionComp->RemvoeAction(this);
	}
	
	GetWorld()->GetTimerManager().ClearTimer(TH_Spaced);
	/*if (GetActionActorComp()->GetOwnerRole() != ENetRole::ROLE_Authority)
	{
		return;
	}*/
	GetWorld()->GetTimerManager().ClearTimer(TH_Persistent);

}
void UYActionEffect::Effect_Implementation(AActor* IncitingActor)
{

}




float UYActionEffect::GetRemainderRuningTime() const
{
	AGameStateBase* GSTE = GetWorld()->GetGameState();
	float ServerTime = 0.0f;
	if (GSTE)
	{
		ServerTime =  GSTE->GetServerWorldTimeSeconds();//获取服务器时间

	}
	return  (StartTime + Persistent) - ServerTime;
}

float UYActionEffect::GetPersistentTime() const
{


	return Persistent;
}

//float UYActionEffect::GetStopedTime() const
//{
//	return (StartTime + Persistent);
//}
