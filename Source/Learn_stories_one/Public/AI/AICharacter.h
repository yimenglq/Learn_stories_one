// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "AICharacter.generated.h"

class UPawnSensingComponent;
class UAI_UserWidget;

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
	UPawnSensingComponent * PawnSensingComp;//感知组件
	UPROPERTY(EditAnywhere,Category = "DIY|Blackboard")
	FName TargetActor;//黑板上的攻击目标

	UPROPERTY(EditAnywhere, Category = "DIY|UI")
	TSubclassOf< UAI_UserWidget> c_BloodUI;//血条UI
	UAI_UserWidget* c_BloodUIIniscte;

	UPROPERTY(VisibleAnywhere)
	class UAttributeActorComponent* c_AttributeActorComp;
public:
	UPROPERTY(EditAnywhere,Category = "DIY|UI")
	FVector	c_UIWorldOffetValue;//世界偏移值UI
	UPROPERTY(EditAnywhere,Category = "DIY|Hit")
	float	c_AIHitFlashSpeed;

public:
	UFUNCTION()
	void OnSeePawnFun(APawn* Pawn);//观测到Pawn时触发

	virtual	void	PostInitializeComponents() override;

	UFUNCTION()
	void OnComponentBeginOverlapFun(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void	OnBlood_volume_ChangedFun(AActor* Actor, UAttributeActorComponent* AttributeActorComp, float Newblood_volume, float DelVal);
	UFUNCTION()
	void	OnDestroyedFun(AActor* DestroyedActor);

};
