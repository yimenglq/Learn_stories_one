// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include <GameplayTagContainer.h>

#include "ActionActorComp.generated.h"



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
	TArray<	TSubclassOf	<class UYAction>> c_ActionsClasses;//所有动作类

	UPROPERTY(Replicated)//该变量 复制
	TArray<	class UYAction*> c_Actions;//类对象  需要使用子对象复制函数
	

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "DIY|Tags")
	FGameplayTagContainer ActiveGameplayTags;

public:
	UFUNCTION(BlueprintCallable,Category = "DIY|Action")
	void AddAction(AActor* IncitingActor,TSubclassOf<UYAction> InActionClss);
	UFUNCTION(BlueprintCallable, Category = "DIY|Action")
	void RemvoeAction(FName const InActionName);
	UFUNCTION(BlueprintCallable, Category = "DIY|Action")
	bool StartAction(AActor* IncitingActor, FName const InActionName);
	UFUNCTION(BlueprintCallable, Category = "DIY|Action")
	bool StopAction(AActor* IncitingActor, FName const InActionName);
	
	UFUNCTION(Server,Reliable)
	void ServerStartAction(AActor* IncitingActor, FName const InActionName);
	UFUNCTION(Server, Reliable)
	void ServerStopAction(AActor* IncitingActor, FName const InActionName);

	UYAction* FindAction(FName const InActionName);


public:

	 bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;



};
