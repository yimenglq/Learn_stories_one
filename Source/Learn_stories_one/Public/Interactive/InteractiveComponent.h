// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include"Engine\EngineTypes.h"
#include "InteractiveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEARN_STORIES_ONE_API UInteractiveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractiveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
protected:
	UPROPERTY(EditAnywhere, Category = "DIY|Interactive")
	float Interactive_Line_end;//直线交互距离
	UPROPERTY(EditDefaultsOnly,Category = "DIY|Interactive|CollisionChannel")
	TSet<	TEnumAsByte<ECollisionChannel> >  CollisionChannels;//碰撞检测的通道

	UPROPERTY(EditDefaultsOnly, Category = "DIY|Interactive")
	TSubclassOf<	class	UYWorldUserWidget> InteractiveUIClss;
	

	class UYWorldUserWidget* InteractiveUI;//交互实例化的UI  可交互显示
	
	FHitResult HitRet;

	AActor*	HitActor;//碰撞到且实现了交互接口的Actor
public:
	UPROPERTY()
	class APawn* OwerPawn;//当前组件依附的Pawn


	bool FindActorIsInteractive();//查询可交互物件

	void	StartInteractive();

};
