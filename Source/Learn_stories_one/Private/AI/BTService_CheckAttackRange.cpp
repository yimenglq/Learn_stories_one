// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_CheckAttackRange.h"
#include"BehaviorTree\BlackboardComponent.h"
#include"AIModule\Classes\AIController.h"


void UBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent * BlackboardComp =  OwnerComp.GetBlackboardComponent();//��ȡ�ڰ����
	if (ensure(BlackboardComp))
	{
		AActor* TargetActor = Cast<AActor>(	BlackboardComp->GetValueAsObject("TargetActor"));//��ȡ�ڰ��еı���
		if (TargetActor)
		{
			AAIController* AIController = OwnerComp.GetAIOwner();//��ȡ����Ϊ�������AI������
			if (AIController)
			{
				APawn* AIPawn =	AIController->GetPawn();//��ȡ�ÿ��������Ƶ�Pawn
				if (AIPawn)
				{
					float Dist = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation() );
					bool bWithinRange = Dist < 2000.0f;
					
					bool bOfSighto = AIController->LineOfSightTo(TargetActor);//AI�Ƿ��ܿ���Ŀ��Actor 
					if (!bOfSighto)
						BlackboardComp->SetValueAsObject("TargetActor", NULL);
					BlackboardComp->SetValueAsBool(bAttackRangeKey.SelectedKeyName,(bWithinRange && bOfSighto));

				}

			}
		
		}



	}

}
