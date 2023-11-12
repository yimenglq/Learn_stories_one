// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/YPlayerController.h"
#include"Blueprint\UserWidget.h"


void AYPlayerController::BeginPlay()
{
	Super::BeginPlay();


	GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Green, L"AYPlayerController::BeginPlay()"+ FString::Printf(L"  Controller: %p",this));

	if (ensure(MainUIClass))
	{
		MainUIIns = CreateWidget(this, MainUIClass);

		if (MainUIIns)
			MainUIIns->AddToViewport();
	}

}
