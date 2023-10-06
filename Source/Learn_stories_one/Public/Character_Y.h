// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character_Y.generated.h"



UCLASS()
class LEARN_STORIES_ONE_API ACharacter_Y : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacter_Y();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	
protected:
	UPROPERTY(EditAnywhere,Category = "DIY")
	TSubclassOf<AActor> FaSeWu;//发射物品

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComp;//弹簧臂组件
	UPROPERTY(EditAnywhere)
	class UCameraComponent* PlayerCameraComp;//摄像机组件

	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere,Category = "DIY|Timer")
	float	TimerRate;

	UPROPERTY(EditAnywhere,Category = "DIY|AnimMontage")
	UAnimMontage*	AnimMontage;

	UPROPERTY(VisibleAnywhere)
	class USkillsActorComponent* SkillsActorComp;

	UPROPERTY(EditAnywhere ,Category = "DIY|Interactive")
	float Interactive_Line_end;//直线交互距离
	UPROPERTY(EditAnywhere, Category = "DIY|UI")
	TSubclassOf<UUserWidget> CrosshairUI;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UAttributeActorComponent* AttributeComp;


	virtual void PostInitializeComponents() override;
public:

	void MoveForward(float Value);

	void MoveRight(float Value);
	

	void StartJump();
	
	void StopJump();
	

	void magic_Spawn();

	void magic_Spawn_Timer();

	void	BlackHole();

	void	Interactive();

	UAttributeActorComponent* GetAttributeComp();
	
	UFUNCTION()
	void OnBldVeChanged(AActor* Actor, UAttributeActorComponent* AttributeActorComp, float Newblood_volume, float DelVal);


};
