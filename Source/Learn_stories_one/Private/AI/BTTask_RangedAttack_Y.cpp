// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_RangedAttack_Y.h"
#include"AIModule\Classes\AIController.h"
#include"GameFramework\Character.h"
#include"AIModule\Classes\BehaviorTree\BlackboardComponent.h"

EBTNodeResult::Type UBTTask_RangedAttack_Y::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	ACharacter* AICharacter =	Cast<ACharacter>(AIController->GetPawn());
	if (AICharacter)
	{
		FVector AIMeshSocketLocation = AICharacter->GetMesh()->GetSocketLocation(AIMEshSocketLocationName);
		
		AActor* TargetActor = Cast<AActor>( OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		if (TargetActor && !TargetActor->IsPendingKillPending())
		{

				FVector TargetActorLocation = TargetActor->GetActorLocation();
				FRotator AItoTargetActor_Rotator = (TargetActorLocation - AIMeshSocketLocation).Rotation();
				FActorSpawnParameters SpawnParameters;
				SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				SpawnParameters.Owner = AICharacter;
				AActor* SpawnAc =	GetWorld()->SpawnActor<AActor>(FaSeWu, AIMeshSocketLocation, AItoTargetActor_Rotator, SpawnParameters);
				
				return SpawnAc ? EBTNodeResult::Succeeded/*³É¹¦*/ : EBTNodeResult::Failed;
		
		}
		else 
		{
			return EBTNodeResult::Failed;

		}
		

	}
	else
	{
		return EBTNodeResult::Failed;//Ê§°Ü
	}
	



	return EBTNodeResult::Failed;
}
