// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/YAction.h"
#include "YActionEffect.generated.h"

/**
 * 
 * ����Ч��  Ĭ�ϳ���ʱ��
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
	float Persistent;//����ʱ��
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Action")
	float Spaced;//ʱ���� ���ڳ���ʱ���еĴ��������

	FTimerHandle TH_Persistent, TH_Spaced;


	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void Effect(AActor* IncitingActor);//����Ч��

public:
	virtual float GetRemainderRuningTime()const override; //��д ʣ�ද��ʱ��
	//virtual float GetStopedTime()const override; //��д ��������ʱ��
	virtual float GetPersistentTime()const override;//��д ��������ʱ��

};
