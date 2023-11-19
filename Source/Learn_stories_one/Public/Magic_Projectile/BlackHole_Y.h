// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Magic_Projectile_Y.h"
#include"Magic_Projectile/Magic_Projectile_Base.h"
#include "BlackHole_Y.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_STORIES_ONE_API ABlackHole_Y : public AMagic_Projectile_Base
{
	GENERATED_BODY()
	

protected:
	virtual void BeginPlay() override;

public:
	ABlackHole_Y();


	virtual void Tick(float DeltaTime) override;



protected:
	UPROPERTY(VisibleAnywhere)
	class	URadialForceComponent* ForceComp;//���������
	UPROPERTY(EditDefaultsOnly,Category = "DIY|ParticleSystem")//EditDefaultsOnly  ˵�������Կ�ͨ�����Դ��ڽ��б༭����ֻ����ԭ���Ͻ��С���˵����������"�ɼ�"˵�����������ݡ�
	class	UParticleSystem* InParticleSystem;//����ϵͳ

public:
	UParticleSystem* GetParticleSystem();



	virtual	void	OnCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



};
