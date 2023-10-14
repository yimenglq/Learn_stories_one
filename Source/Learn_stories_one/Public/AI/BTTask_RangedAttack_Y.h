// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RangedAttack_Y.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_STORIES_ONE_API UBTTask_RangedAttack_Y : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere,Category = "DIY|AI|Mesh")
	FName AIMEshSocketLocationName;
	UPROPERTY(EditAnywhere, Category = "DIY|AI")
	TSubclassOf<AActor> FaSeWu;


public:


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;

};
