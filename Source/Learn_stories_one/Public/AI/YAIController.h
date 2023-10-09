// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "YAIController.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_STORIES_ONE_API AYAIController : public AAIController
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;


protected:
	UPROPERTY(EditDefaultsOnly,Category = "DIY|BehaviorTree")
	UBehaviorTree* BehaviorTree;


};
