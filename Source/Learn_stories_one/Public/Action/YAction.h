// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include"GameplayTagContainer.h"
#include "YAction.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionStarted, UActionActorComp*, OwnerActionComp, UYAction*, ActionIns);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionStoped, UActionActorComp*, OwnerActionComp, UYAction*, ActionIns);

USTRUCT()
struct FOnRepParm
{
	GENERATED_BODY()


	UPROPERTY()
	bool bIsRuningServer;//服务器端正在运行？
	UPROPERTY()
	AActor* IncitingActor;//传递的参数
};

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
	FOnRepParm RepParm;
	
	UPROPERTY(Replicated,BlueprintReadOnly, Category = "DIY|Action")
	float StartTime;//动作开始的时间

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly, Category = "DIY|Action")
	UTexture2D* ActionIcon;//动作附带的图片 (通常是有持续效果的动作使用 如 持续伤害)


	UFUNCTION()
	void OnRep_IsRuning();
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DIY|Action")
	bool bStart_Adter_Load { false };//加载后即可开始

protected:



	UFUNCTION(BlueprintCallable,Category = "DIY|Action")
	class	UActionActorComp* GetActionActorComp()const;//获得播放该动作的 动作组件

public:
	UPROPERTY(BlueprintAssignable,Category="DIY|Action|Event")
	FOnActionStarted OnActionStarted;//动画开始播放时
	UPROPERTY(BlueprintAssignable, Category = "DIY|Action|Event")
	FOnActionStoped OnActionStoped;//动画停止播放时
	UPROPERTY(EditDefaultsOnly,Category = "Action")
	FName ActionName;//动作的名称



	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
	void StartAction(AActor* IncitingActor);
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category = "Action")
	void StopAction(AActor* IncitingActor);
	UFUNCTION(BlueprintNativeEvent,Category = "Action")
	bool IsCanStart(AActor* IncitingActor);
	UFUNCTION(BlueprintCallable, Category = "Action")
	bool IsRuning()const;
	UFUNCTION(BlueprintCallable,Category="Action")
	virtual float GetRemainderRuningTime()const { return 0.0f; }//动作剩余时间
	UFUNCTION(BlueprintCallable, Category = "Action")
	virtual float GetStopedTime()const { return 0.0f; }//动作结束时间
	UFUNCTION(BlueprintCallable, Category = "Action")
	virtual float GetPersistentTime()const { return 0.0f; }//动作持续时间

	UWorld*	GetWorld()const;

	virtual void Action(UObject** out) {}

	 bool IsSupportedForNetworking() const override //可以联网复制

	{
		 return true;
	}

	


};
