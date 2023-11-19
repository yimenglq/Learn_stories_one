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
	UStaticMeshComponent* StaticMeshCompBase;//底座
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMeshCompLid;//盖盖
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
	bool bLidOpened;//打开盖子
	
	UFUNCTION()
	void OnRep_LidOpened();// bLidOpened改变时触发 打开盖子时的触发函数  客户端自动触发  服务器需要在服务器运行函数中

public:

	void	Interactive_Implementation(APawn* InOwPawn)override;

	UFUNCTION()
	void timeLinefunion(float Output);

	virtual	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
