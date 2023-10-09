// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/YAIController.h"
#include <Kismet/GameplayStatics.h>
#include"BehaviorTree\BlackboardComponent.h"

void AYAIController::BeginPlay()
{
	Super::BeginPlay();
	if (BehaviorTree)
	{

		RunBehaviorTree(BehaviorTree);//������Ϊ��
		APawn* PlayPawn = UGameplayStatics::GetPlayerController(this, 0)->GetPawn();
		if (PlayPawn)
		{
			GetBlackboardComponent()->SetValueAsVector(TEXT("MoveToLocation"), PlayPawn->GetActorLocation());
			GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), PlayPawn);//��ڰ���ı�������ֵ ��Ӧ����

		}

	}
}
