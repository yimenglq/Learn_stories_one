// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "YSaveGameBase.generated.h"

USTRUCT()
struct FSaveDate
{

	GENERATED_BODY()

	UPROPERTY()
	FString Name;
	UPROPERTY()
	FTransform Transform;
	UPROPERTY()
	TArray<uint8> ByteDate;


};
/**
 * 
 */
UCLASS()
class LEARN_STORIES_ONE_API UYSaveGameBase : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	uint32 Id;
	UPROPERTY()
	TArray<	FSaveDate> SaveDates;

};
