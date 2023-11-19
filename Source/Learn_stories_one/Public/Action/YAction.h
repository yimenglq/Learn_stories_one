// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include"GameplayTagContainer.h"
#include "YAction.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)//将此类公开为用于创建蓝图的可接受基类。默认为`NotBlueprintable`，除非继承时就并非如此。此说明符由子类继承。 可以以此创建蓝图
class LEARN_STORIES_ONE_API UYAction : public UObject
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DIY|Action|Tags")
	FGameplayTagContainer GrantsTags;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DIY|Action|Tags")
	FGameplayTagContainer BlokTags;
	//UPROPERTY(ReplicatedUsing = "OnRep_IsRuning")
	bool bIsRuning;//正在运行？
	UPROPERTY(ReplicatedUsing = "OnRep_IsRuning")
	bool bIsRuningServer;//服务器端正在运行？
	
	UFUNCTION()
	void OnRep_IsRuning();
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DIY|Action")
	bool bStart_Adter_Load { false };//加载后即可开始

protected:

	UFUNCTION(BlueprintCallable,Category = "DIY|Action")
	class	UActionActorComp* GetActionActorComp()const;

public:




	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
	void StartAction(AActor* IncitingActor);
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category = "Action")
	void StopAction(AActor* IncitingActor);
	UFUNCTION(BlueprintNativeEvent,Category = "Action")
	bool IsCanStart(AActor* IncitingActor);
	UFUNCTION(BlueprintCallable, Category = "Action")
	bool IsRuning()const;

	UPROPERTY(EditDefaultsOnly,Category = "Action")
	FName ActionName;//动作的名称

	UWorld*	GetWorld();

	virtual void Action(UObject** out) {}

	 bool IsSupportedForNetworking() const override

	{
		 return true;
	}


};
