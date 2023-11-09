// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/YAction.h"
#include "YActionEffect.generated.h"

/**
 * 
 * 动作效果  默认持续时间
 * 
 */
UCLASS()
class LEARN_STORIES_ONE_API UYActionEffect : public UYAction
{
	GENERATED_BODY()
	


public:
	//UYAction override
	void StartAction_Implementation(AActor* IncitingActor) override;

	void StopAction_Implementation(AActor* IncitingActor) override;
	
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Action")
	float Persistent;//持续时间
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Action")
	float Spaced;//时间间隔 （在持续时间中的触发间隔）

	FTimerHandle TH_Persistent, TH_Spaced;


	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void Effect(AActor* IncitingActor);//动作效果

public:




};
