// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/YPlayerState.h"
#include "SaveGame/YSaveGameBase.h"


void AYPlayerState::SavePlayerState_Implementation( UYSaveGameBase* InSaveObj)
{
	if (InSaveObj)
	{
		InSaveObj->Id = Id;

	}
	
}

void AYPlayerState::LoadPlayerState_Implementation( UYSaveGameBase* InSaveObj)
{
	if (InSaveObj)
	{
		Id = InSaveObj->Id;

	}
}
