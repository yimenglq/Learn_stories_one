// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include <GameplayTagContainer.h>

#include "ActionActorComp.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionCompStarted, UActionActorComp*, OwnerActionComp, UYAction*, ActionIns);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionCompStoped, UActionActorComp*, OwnerActionComp, UYAction*, ActionIns);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEARN_STORIES_ONE_API UActionActorComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActionActorComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
protected:
	UPROPERTY(EditAnywhere,Category="DIY|ActionClass")
	TArray<	TSubclassOf	<class UYAction>> c_ActionsClasses;//���ж�����

	UPROPERTY(Replicated)//�ñ��� ����
	TArray<	class UYAction*> c_Actions;//�����  ��Ҫʹ���Ӷ����ƺ���
	

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "DIY|Tags")
	FGameplayTagContainer ActiveGameplayTags;

public:

	UPROPERTY(BlueprintAssignable, Category = "DIY|ActionComp|Event")
	FOnActionCompStarted OnActionCompStarted; //������ʼ ʱ
	UPROPERTY(BlueprintAssignable, Category = "DIY|ActionComp|Event")
	FOnActionCompStoped OnActionCompStoped; //����ֹͣ ʱ

	UFUNCTION(BlueprintCallable,Category = "DIY|Action")
	void AddAction(AActor* IncitingActor,TSubclassOf<UYAction> InActionClss);
	UFUNCTION(BlueprintCallable, Category = "DIY|Action")
	void RemvoeAction(FName const InActionName);

	//UFUNCTION(BlueprintCallable, Category = "DIY|Action")
	void RemvoeAction(UYAction * ReActionObj);

	UFUNCTION(BlueprintCallable, Category = "DIY|Action")
	bool StartAction(AActor* IncitingActor, FName const InActionName);
	UFUNCTION(BlueprintCallable, Category = "DIY|Action")
	bool StopAction(AActor* IncitingActor, FName const InActionName);
	
	UFUNCTION(Server,Reliable)
	void ServerStartAction(AActor* IncitingActor, FName const InActionName);
	UFUNCTION(Server, Reliable)
	void ServerStopAction(AActor* IncitingActor, FName const InActionName);

	UYAction* FindAction(FName const InActionName);

/// �����¼�����
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void OnStartActionFu(UActionActorComp* OwnerActionComp, UYAction* ActionIns);
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void OnStopActionFu(UActionActorComp* OwnerActionComp, UYAction* ActionIns);

	UFUNCTION(NetMulticast,Unreliable)
	void BindActionFu(UYAction* NewAction);


	/// </summary>

public:

	 bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;



};
