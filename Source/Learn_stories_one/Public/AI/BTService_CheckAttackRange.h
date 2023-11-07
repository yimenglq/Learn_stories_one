// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_STORIES_ONE_API UBTService_CheckAttackRange : public UBTService
{
	GENERATED_BODY()
	


protected:
	UPROPERTY(EditAnywhere,Category = "DIY|AI")
	FBlackboardKeySelector bAttackRangeKey;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	FTimerHandle	c_TimerHandle;

};
