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
	UAnimMontage*	AnimMontage;//动画 蒙太奇

	UPROPERTY(VisibleAnywhere)
	class USkillsActorComponent* SkillsActorComp;
	UPROPERTY(VisibleAnywhere)
	class	UInteractiveComponent* InteractiveComp;//交互组件
	
	
	
	UPROPERTY(EditAnywhere, Category = "DIY|UI")
	TSubclassOf<UUserWidget> CrosshairUI;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UAttributeActorComponent* AttributeComp;//属性组件
	UPROPERTY(EditAnywhere, Category = "DIY|CameraShake")
	TSubclassOf<class UCameraShakeBase> CameraShake;

	UPROPERTY(VisibleAnywhere)
	class UActionActorComp* ActionActorComp;//动作模块组件
	virtual void PostInitializeComponents() override;

	UFUNCTION(Server, Reliable)
	void Server_Interactive();//服务器运行函数

public:

	void MoveForward(float Value);

	void MoveRight(float Value);
	

	void StartJump();
	
	void StopJump();
	
	void SatrtSprint();

	void StopSprint();


	void magic_Spawn();
	void magic_Spawned();
	void Teleportation();


	void magic_Spawn_Timer();

	void	BlackHole();

	void	Interactive();
	


	
	UAttributeActorComponent* GetAttributeComp();
	UCameraComponent* GetCameraComponent();
	UActionActorComp* GetActionActorComp() const;

	friend class UYMagicProjectileAction;
public:

	//委托触发函数 start
	UFUNCTION()
	void OnBldVeChanged(AActor* Actor, UAttributeActorComponent* AttributeActorComp, float Newblood_volume, float DelVal);

	UFUNCTION()
	void	OnCapsuleCompOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	// end
	UFUNCTION()
	void	ClientStopCameraShake();

	UFUNCTION()
	void ClientStartCameraShake();

	
};
