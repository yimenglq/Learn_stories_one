// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/YAction.h"
#include "YMagicProjectileAction.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_STORIES_ONE_API UYMagicProjectileAction : public UYAction
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(EditAnywhere, Category = "DIY")
	TSubclassOf<class AActor> MagicProjectileClass;//������Ʒ

	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, Category = "DIY|Timer")
	float	TimerRate;

	UPROPERTY(EditAnywhere, Category = "DIY|AnimMontage")
	class UAnimMontage* AnimMontage;
	UPROPERTY(EditAnywhere, Category = "DIY|Socket")
	FName	SocketName;

	AActor* SpawnMagicProjectile;//�������ɵĶ���

	UPROPERTY(EditDefaultsOnly,Category = "DIY|Range")//���  ����׼�ǵľ���
	FVector  Range {0,0,0};
public:
	UYMagicProjectileAction();
	
	//UFUNCTION(BlueprintNativeEvent, Category = "Action")
	virtual	void StartAction_Implementation(AActor* IncitingActor) override;
	//UFUNCTION(BlueprintNativeEvent, Category = "Action")
	virtual	void StopAction_Implementation(AActor* IncitingActor) override;


	UFUNCTION()
	void MagicProjectileSpawn(class	ACharacter_Y* IncitingACharacter);

	virtual	AActor* GetSpawnMagicProjectile() const;

	virtual void Action(UObject** out) override;
};
