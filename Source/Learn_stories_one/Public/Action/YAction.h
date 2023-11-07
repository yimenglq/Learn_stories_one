// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "YAction.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)//将此类公开为用于创建蓝图的可接受基类。默认为`NotBlueprintable`，除非继承时就并非如此。此说明符由子类继承。 可以以此创建蓝图
class LEARN_STORIES_ONE_API UYAction : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent,Category = "Action")
	void StartAction(AActor* IncitingActor);
	UFUNCTION(BlueprintNativeEvent,Category = "Action")
	void StopAction(AActor* IncitingActor);
	UPROPERTY(EditDefaultsOnly,Category = "Action")
	FName ActionName;//动作的名称

	UWorld*	GetWorld();

	virtual void Action(UObject** out) {}

};
