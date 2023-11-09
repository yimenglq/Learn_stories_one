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
	FVector HitPoint;//ײ��λ��

protected:
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereComp;//������ײ
	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent*  ProjectileMovementComp;//�����ƶ�
	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* ParticleSystemComp;//����

	UPROPERTY(EditAnywhere,Category = "DIY|Attribute")
	int Hurt;//�˺�
	UPROPERTY(EditDefaultsOnly, Category = "DIY|Attribute")
	TSubclassOf<class UYActionEffect> ActionEffect;//���踽�ӵĶ���Ч��  ��������˺�


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DIY|Sound")
	class USoundBase* LaunchSound;//����ʱ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "DIY|Sound")
	class USoundBase* CollidingSound;//��ײʱ������


	UFUNCTION()
	virtual	void	OnCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual	void OnCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION()
	virtual void OnCompEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	

public:

	bool	live:1;//�Ƿ���

	UFUNCTION()
	void	Destroy();


};
