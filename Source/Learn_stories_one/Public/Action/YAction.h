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
	bool bIsRuningServer;//���������������У�
	UPROPERTY()
	AActor* IncitingActor;//���ݵĲ���
};

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
	//UPROPERTY(ReplicatedUsing = "OnRep_IsRuning")
	bool bIsRuning;//�������У�
	UPROPERTY(ReplicatedUsing = "OnRep_IsRuning")
	FOnRepParm RepParm;
	
	UPROPERTY(Replicated,BlueprintReadOnly, Category = "DIY|Action")
	float StartTime;//������ʼ��ʱ��

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly, Category = "DIY|Action")
	UTexture2D* ActionIcon;//����������ͼƬ (ͨ�����г���Ч���Ķ���ʹ�� �� �����˺�)


	UFUNCTION()
	void OnRep_IsRuning();
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DIY|Action")
	bool bStart_Adter_Load { false };//���غ󼴿ɿ�ʼ

protected:



	UFUNCTION(BlueprintCallable,Category = "DIY|Action")
	class	UActionActorComp* GetActionActorComp()const;//��ò��Ÿö����� �������

public:
	UPROPERTY(BlueprintAssignable,Category="DIY|Action|Event")
	FOnActionStarted OnActionStarted;//������ʼ����ʱ
	UPROPERTY(BlueprintAssignable, Category = "DIY|Action|Event")
	FOnActionStoped OnActionStoped;//����ֹͣ����ʱ
	UPROPERTY(EditDefaultsOnly,Category = "Action")
	FName ActionName;//����������



	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
	void StartAction(AActor* IncitingActor);
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category = "Action")
	void StopAction(AActor* IncitingActor);
	UFUNCTION(BlueprintNativeEvent,Category = "Action")
	bool IsCanStart(AActor* IncitingActor);
	UFUNCTION(BlueprintCallable, Category = "Action")
	bool IsRuning()const;
	UFUNCTION(BlueprintCallable,Category="Action")
	virtual float GetRemainderRuningTime()const { return 0.0f; }//����ʣ��ʱ��
	UFUNCTION(BlueprintCallable, Category = "Action")
	virtual float GetStopedTime()const { return 0.0f; }//��������ʱ��
	UFUNCTION(BlueprintCallable, Category = "Action")
	virtual float GetPersistentTime()const { return 0.0f; }//��������ʱ��

	UWorld*	GetWorld()const;

	virtual void Action(UObject** out) {}

	 bool IsSupportedForNetworking() const override //������������

	{
		 return true;
	}

	


};
