// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "YPlayerState.generated.h"




class UYSaveGameBase;
/**
 * 
 */
UCLASS()
class LEARN_STORIES_ONE_API AYPlayerState : public APlayerState
{
	GENERATED_BODY()
	



protected:
	uint32 Id;
	
	

public:

	UFUNCTION(BlueprintNativeEvent)
	void SavePlayerState( UYSaveGameBase* InSaveObj);
	UFUNCTION(BlueprintNativeEvent)
	void LoadPlayerState( UYSaveGameBase* InSaveObj);

};
