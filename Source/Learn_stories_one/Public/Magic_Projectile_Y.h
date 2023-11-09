// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Magic_Projectile_Y.generated.h"


UCLASS()
class LEARN_STORIES_ONE_API AMagic_Projectile_Y : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagic_Projectile_Y();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents()override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	FVector HitPoint;//撞击位置

protected:
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereComp;//球形碰撞
	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent*  ProjectileMovementComp;//球形移动
	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* ParticleSystemComp;//粒子

	UPROPERTY(EditAnywhere,Category = "DIY|Attribute")
	int Hurt;//伤害
	UPROPERTY(EditDefaultsOnly, Category = "DIY|Attribute")
	TSubclassOf<class UYActionEffect> ActionEffect;//弹丸附加的动作效果  比如持续伤害


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DIY|Sound")
	class USoundBase* LaunchSound;//发射时的声音
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "DIY|Sound")
	class USoundBase* CollidingSound;//碰撞时的声音


	UFUNCTION()
	virtual	void	OnCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual	void OnCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION()
	virtual void OnCompEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	

public:

	bool	live:1;//是否存活

	UFUNCTION()
	void	Destroy();


};
