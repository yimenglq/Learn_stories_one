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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereComp;//������ײ
	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent*  ProjectileMovementComp;//�����ƶ�
	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* ParticleSystemComp;//����

	UPROPERTY(EditAnywhere,Category = "DIY|Attribute")
	int Hurt;


	UFUNCTION()
	virtual	void	OnCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual	void OnCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	

public:

	bool	live:1;//�Ƿ���

	void	Destroy();


};
