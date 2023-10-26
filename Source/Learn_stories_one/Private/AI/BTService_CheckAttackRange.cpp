// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_CheckAttackRange.h"
#include"BehaviorTree\BlackboardComponent.h"
#include"AIModule\Classes\AIController.h"


void UBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent * BlackboardComp =  OwnerComp.GetBlackboardComponent();//获取黑板组件
	if (ensure(BlackboardComp))
	{
		AActor* TargetActor = Cast<AActor>(	BlackboardComp->GetValueAsObject("TargetActor"));//获取黑板中的变量
		if (TargetActor)
		{
			AAIController* AIController = OwnerComp.GetAIOwner();//获取该行为树组件的AI控制器
			if (AIController)
			{
				APawn* AIPawn =	AIController->GetPawn();//获取该控制器控制的Pawn
				if (AIPawn)
				{
					float Dist = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation() );
					bool bWithinRange = Dist < 2000.0f;
					
					bool bOfSighto = AIController->LineOfSightTo(TargetActor);//AI是否能看到目标Actor 
					if (!bOfSighto)
						BlackboardComp->SetValueAsObject("TargetActor", NULL);
					BlackboardComp->SetValueAsBool(bAttackRangeKey.SelectedKeyName,(bWithinRange && bOfSighto));

				}

			}
		
		}



	}

}
