// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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
	TArray<	TSubclassOf	<class UYAction>> c_ActionsClasses;//���ж�����

	UPROPERTY()
	TArray<	class UYAction*> c_Actions;

public:
	UFUNCTION(BlueprintCallable,Category = "DIY|Action")
	void AddAction(TSubclassOf<UYAction> InActionClss);
	UFUNCTION(BlueprintCallable, Category = "DIY|Action")
	void RemvoeAction(FName const InActionName);

	bool StartAction(AActor* IncitingActor, FName const InActionName);

	bool StopAction(AActor* IncitingActor, FName const InActionName);

	UYAction* FindAction(FName const InActionName);
};