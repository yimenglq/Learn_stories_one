// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "YPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewPawn, APawn*, NewPawn);

USTRUCT()
struct FActionKey
{
	GENERATED_USTRUCT_BODY()

	/** Friendly name of action, e.g "jump" */
	UPROPERTY(EditAnywhere, Category = "Input")
	FName ActionName;

	UPROPERTY(EditAnywhere, Category = "Input")
	FKey Key;

	UPROPERTY(EditAnywhere, Category = "Input")
	uint8 bShift : 1;

	/** true if one of the Ctrl keys must be down when the KeyEvent is received to be acknowledged */
	UPROPERTY(EditAnywhere, Category = "Input")
	uint8 bCtrl : 1;

	/** true if one of the Alt keys must be down when the KeyEvent is received to be acknowledged */
	UPROPERTY(EditAnywhere, Category = "Input")
	uint8 bAlt : 1;

	/** true if one of the Cmd keys must be down when the KeyEvent is received to be acknowledged */
	UPROPERTY(EditAnywhere, Category = "Input")
	uint8 bCmd : 1;

};

/**
 * 
 */
UCLASS()
class LEARN_STORIES_ONE_API AYPlayerController : public APlayerController
{
	GENERATED_BODY()
	


public:
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, Category = "DIY|UI")
	TSubclassOf<class UUserWidget> MainUIClass;//����ui
	class UUserWidget* MainUIIns;//����uiʵ��

	UPROPERTY(EditDefaultsOnly, Category = "DIY|UI")
	TSubclassOf<class UUserWidget> PausedMenuUIClass;//��ͣ�˵�ui Class
	class UUserWidget* PausedMenuUIIns;//��ͣ�˵�uiʵ��
	UPROPERTY(EditDefaultsOnly, Category = "DIY|UI")
	FActionKey PausedKey;

public:
	UPROPERTY(BlueprintAssignable,Category = "DIY|PlayerController|Event")
	FOnNewPawn OnSetPawn;// ����pawnʱ���õ�ί��

	virtual void SetPawn(APawn* InPawn) override;
	UFUNCTION(BlueprintCallable,Category = "DIY|PlayerController")
	void	PausedMenu();//��ͣ�˵��߼�

	virtual void SetupInputComponent()override;
	
};
