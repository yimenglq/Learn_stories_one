// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/YPlayerController.h"
#include"Blueprint\UserWidget.h"
#include <GameFramework/PlayerInput.h>
#include <Kismet/GameplayStatics.h>


void AYPlayerController::BeginPlay()
{
	Super::BeginPlay();

	

	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, L"AYPlayerController::SetupInputComponent()");
	GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Green, L"AYPlayerController::BeginPlay()"+ FString::Printf(L"  Controller: %p",this));

	if(IsLocalController())//判断该玩家控制器是否是本地控制器
		if (ensure(MainUIClass))
		{
			MainUIIns = CreateWidget(this, MainUIClass);

			if (MainUIIns)
				MainUIIns->AddToViewport();
		}

}

void AYPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	
	static float Oldtime = 0;
	static float NewTime = 0;
	NewTime = GetWorld()->GetTimeSeconds();
	if (( NewTime - Oldtime ) > 1.0)
	{
		Oldtime = NewTime;
	
	  static int n = 0;
		if (n < PlayerInput->ActionMappings.Num())
		{
			GEngine->AddOnScreenDebugMessage(0, 1, FColor::Black, FString::Printf(TEXT("PlayerInput,ActionMappings: %s"), *PlayerInput->ActionMappings[n].ActionName.ToString()));
			n++;
		}
		else
		{
			n = 0;
		}
	}

}

void AYPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	OnSetPawn.Broadcast(InPawn);
}

void AYPlayerController::PausedMenu()
{
	
	if (PausedMenuUIIns && PausedMenuUIIns->IsInViewport())
	{
		PausedMenuUIIns->RemoveFromParent();
		PausedMenuUIIns = nullptr;
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());//游戏输入模式
		return;
	}
	ensureAlways(PausedMenuUIClass);
	PausedMenuUIIns = 	CreateWidget(this, PausedMenuUIClass);
	if (PausedMenuUIIns)
	{
		bShowMouseCursor = true;
		SetInputMode(FInputModeUIOnly());//UI输入模式
		int32 wx, wy;
		GetViewportSize(wx, wy);//获取屏幕大小
		SetMouseLocation(wx/2,wy/2);//设置鼠标位置
		PausedMenuUIIns->AddToViewport();

	}
}

void AYPlayerController::SetupInputComponent()
{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, L"AYPlayerController::SetupInputComponent()");
	Super::SetupInputComponent();
	
	if (PausedKey.ActionName == NAME_None)
	{
		PausedKey.ActionName = "Pause";
		PausedKey.Key = EKeys::O;
	}
	FInputActionKeyMapping SprintKeyMap(PausedKey.ActionName, PausedKey.Key, PausedKey.bShift, PausedKey.bCtrl, PausedKey.bAlt, PausedKey.bCmd);
	PlayerInput->AddActionMapping(SprintKeyMap);
	InputComponent->BindAction(PausedKey.ActionName, IE_Pressed, this, &AYPlayerController::PausedMenu);
	//InputComponent->BindAction(Sprint, IE_Released, this, &AYPlayerController::PausedMenu);



}


