// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YWorldUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_STORIES_ONE_API UYWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()
	




public:


	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:

	UYWorldUserWidget* WorldUI;//��������ʾ��UI

	APawn* OwerPawn;//UIӵ���� �� ��ҵ�pawn �� 

	AActor* UIToWordActor;//	UI���ӵ������actor��

	UPROPERTY(EditAnywhere,Category = "UI")
	FVector WorldOff {0,0,0};//���ӵ�actor���������ƫ��


	friend	class UInteractiveComponent;
};
