// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"
class UPawnSensingComponent;

UCLASS()
class LEARN_STORIES_ONE_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent * PawnSensingComp;
	UPROPERTY(EditAnywhere,Category = "DIY|Blackboard")
	FName TargetActor;

public:
	UFUNCTION()
	void OnSeePawnFun(APawn* Pawn);

	virtual	void	PostInitializeComponents() override;
};
