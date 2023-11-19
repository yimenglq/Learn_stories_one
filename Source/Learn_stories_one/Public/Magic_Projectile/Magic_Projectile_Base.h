// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Magic_Projectile_Base.generated.h"

UCLASS()
class LEARN_STORIES_ONE_API AMagic_Projectile_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagic_Projectile_Base();

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
	class UProjectileMovementComponent* ProjectileMovementComp;//�����ƶ�
	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* ParticleSystemComp;//����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DIY|Sound")
	class USoundBase* LaunchSound;//����ʱ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DIY|Sound")
	class USoundBase* CollidingSound;//��ײʱ������

	

};
