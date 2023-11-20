// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "YPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewPawn, APawn*, NewPawn);
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
	TSubclassOf<class UUserWidget> MainUIClass;//����ui
	class UUserWidget* MainUIIns;//����uiʵ��

public:
	UPROPERTY(BlueprintAssignable,Category = "DIY|PlayerController|Event")
	FOnNewPawn OnSetPawn;// ����pawnʱ���õ�ί��

	virtual void SetPawn(APawn* InPawn) override;

};
