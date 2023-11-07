// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "YAction.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)//�����๫��Ϊ���ڴ�����ͼ�Ŀɽ��ܻ��ࡣĬ��Ϊ`NotBlueprintable`�����Ǽ̳�ʱ�Ͳ�����ˡ���˵����������̳С� �����Դ˴�����ͼ
class LEARN_STORIES_ONE_API UYAction : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent,Category = "Action")
	void StartAction(AActor* IncitingActor);
	UFUNCTION(BlueprintNativeEvent,Category = "Action")
	void StopAction(AActor* IncitingActor);
	UPROPERTY(EditDefaultsOnly,Category = "Action")
	FName ActionName;//����������

	UWorld*	GetWorld();

	virtual void Action(UObject** out) {}

};
