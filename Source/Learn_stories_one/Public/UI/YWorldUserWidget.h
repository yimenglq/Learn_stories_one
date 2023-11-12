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

	UYWorldUserWidget* WorldUI;//在世界显示的UI

	APawn* OwerPawn;//UI拥有者 （ 玩家的pawn ） 

	AActor* UIToWordActor;//	UI附加到世界的actor上

	UPROPERTY(EditAnywhere,Category = "UI")
	FVector WorldOff {0,0,0};//附加到actor上世界相对偏移


	friend	class UInteractiveComponent;
};
