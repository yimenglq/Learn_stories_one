// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"Interactive_Interface.h"
#include "TreasureChestsActor.generated.h"

UCLASS()
class LEARN_STORIES_ONE_API ATreasureChestsActor : public AActor, public IInteractive_Interface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATreasureChestsActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMeshCompBase;//����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMeshCompLid;//�Ǹ�
	UPROPERTY(EditAnywhere,Category = "DIY|Lid")
	float LidPitch;
	UPROPERTY(EditAnywhere, Category = "DIY|Lid")
	float  LidYaw;
	UPROPERTY(EditAnywhere, Category = "DIY|Lid")
	float LidRoll;

	UPROPERTY(VisibleAnywhere,Replicated)
	class UTimelineComponent* TimeLineComp;

	UPROPERTY(VisibleAnywhere)
	UCurveFloat* CurveFloat;

	

	UPROPERTY(ReplicatedUsing = "OnRep_LidOpened", BlueprintReadOnly)
	bool bLidOpened;//�򿪸���
	
	UFUNCTION()
	void OnRep_LidOpened();// bLidOpened�ı�ʱ���� �򿪸���ʱ�Ĵ�������  �ͻ����Զ�����  ��������Ҫ�ڷ��������к�����

public:

	void	Interactive_Implementation(APawn* InOwPawn)override;

	UFUNCTION()
	void timeLinefunion(float Output);

	virtual	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
