// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AI_UserWidget.generated.h"

/**
 * 
 */
	
	

class USizeBox;
UCLASS()
class LEARN_STORIES_ONE_API UAI_UserWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:

	
	struct FScalarParameterValue
	{
		UPROPERTY(EditAnywhere,Category = "DIY|ParameterName")
		FName ParameterName;
		float Value;

	};

protected:


	UPROPERTY(meta = (BindWidget))
	USizeBox* c_SizeBoxBlood;
	UPROPERTY(meta = (BindWidget))
	class UImage* c_Bloodimg;
	

	//UPROPERTY(EditAnywhere,Category = "DIY|UI|Met")
	FScalarParameterValue c_ScalarParameterValue;//±Í¡ø÷µ
	UPROPERTY(EditAnywhere, Category = "DIY|UI|Met")
	FName c_ParameterName;

	

public:
	FVector c_WorldOffetValue;
	float c_OldBlood,c_NewBlood;
	

public:
	UAI_UserWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime)override;

	UPROPERTY(BlueprintReadOnly,Category = "DIY|UI");
	AActor* c_AttachedActor;




	/*UPROPERTY(BlueprintReadOnly, Category = "DIY|UI");
	virtual FReply NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);*/
};
