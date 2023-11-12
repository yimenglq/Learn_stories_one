// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "YPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_STORIES_ONE_API AYPlayerController : public APlayerController
{
	GENERATED_BODY()
	


public:
	virtual void BeginPlay() override;


protected:
	UPROPERTY(EditAnywhere, Category = "DIY|UI")
	TSubclassOf<class UUserWidget> MainUIClass;//界面ui
	class UUserWidget* MainUIIns;//界面ui实例




};
