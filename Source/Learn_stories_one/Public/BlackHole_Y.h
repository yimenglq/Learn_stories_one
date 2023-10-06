// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Magic_Projectile_Y.h"
#include "BlackHole_Y.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_STORIES_ONE_API ABlackHole_Y : public AMagic_Projectile_Y
{
	GENERATED_BODY()
	

public:
	ABlackHole_Y();


	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
	class	URadialForceComponent* ForceComp;
	UPROPERTY(EditDefaultsOnly,Category = "DIY|ParticleSystem")//EditDefaultsOnly  说明此属性可通过属性窗口进行编辑，但只能在原型上进行。此说明符与所有"可见"说明符均不兼容。
	class	UParticleSystem* InParticleSystem;

public:
	UParticleSystem* GetParticleSystem();



	virtual	void	OnCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)override;



};
