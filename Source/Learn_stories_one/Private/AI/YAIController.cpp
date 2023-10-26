// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/YAIController.h"
#include <Kismet/GameplayStatics.h>
#include"BehaviorTree\BlackboardComponent.h"

void AYAIController::BeginPlay()
{
	Super::BeginPlay();
	if (ensureMsgf(BehaviorTree,TEXT("行为树为空，查看，细节面板是否赋予了行为树模板。")))
	{

		RunBehaviorTree(BehaviorTree);//运行行为树
		//APawn* PlayPawn = UGameplayStatics::GetPlayerController(this, 0)->GetPawn();
		//if (PlayPawn)
		//{
		//	GetBlackboardComponent()->SetValueAsVector(TEXT("MoveToLocation"), PlayPawn->GetActorLocation());
		//	GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), PlayPawn);//向黑板里的变量填入值 对应名称

		//}

	}
}
