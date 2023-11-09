// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include"GameplayTagContainer.h"
#include "YAction.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)//�����๫��Ϊ���ڴ�����ͼ�Ŀɽ��ܻ��ࡣĬ��Ϊ`NotBlueprintable`�����Ǽ̳�ʱ�Ͳ�����ˡ���˵����������̳С� �����Դ˴�����ͼ
class LEARN_STORIES_ONE_API UYAction : public UObject
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DIY|Action|Tags")
	FGameplayTagContainer GrantsTags;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DIY|Action|Tags")
	FGameplayTagContainer BlokTags;

	bool bIsRuning;//�������У�

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DIY|Action")
	bool bStart_Adter_Load { false };//���غ󼴿ɿ�ʼ

protected:

	UFUNCTION(BlueprintCallable,Category = "DIY|Action")
	class	UActionActorComp* GetActionActorComp()const;

public:




	UFUNCTION(BlueprintNativeEvent,Category = "Action")
	void StartAction(AActor* IncitingActor);
	UFUNCTION(BlueprintNativeEvent,Category = "Action")
	void StopAction(AActor* IncitingActor);
	UFUNCTION(BlueprintNativeEvent,Category = "Action")
	bool IsCanStart(AActor* IncitingActor);
	UFUNCTION(BlueprintCallable, Category = "Action")
	bool IsRuning()const;

	UPROPERTY(EditDefaultsOnly,Category = "Action")
	FName ActionName;//����������

	UWorld*	GetWorld();

	virtual void Action(UObject** out) {}

};
