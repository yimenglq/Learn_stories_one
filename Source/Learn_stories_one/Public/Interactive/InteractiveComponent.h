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
	float Interactive_Line_end;//ֱ�߽�������
	UPROPERTY(EditDefaultsOnly,Category = "DIY|Interactive|CollisionChannel")
	TSet<	TEnumAsByte<ECollisionChannel> >  CollisionChannels;//��ײ����ͨ��

	UPROPERTY(EditDefaultsOnly, Category = "DIY|Interactive")
	TSubclassOf<	class	UYWorldUserWidget> InteractiveUIClss;
	

	class UYWorldUserWidget* InteractiveUI;//����ʵ������UI  �ɽ�����ʾ
	
	FHitResult HitRet;

	AActor*	HitActor;//��ײ����ʵ���˽����ӿڵ�Actor
public:
	UPROPERTY()
	class APawn* OwerPawn;//��ǰ���������Pawn


	bool FindActorIsInteractive();//��ѯ�ɽ������

	void	StartInteractive();

};
