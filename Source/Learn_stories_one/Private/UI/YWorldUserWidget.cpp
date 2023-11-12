// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/YWorldUserWidget.h"
#include <Kismet/GameplayStatics.h>
#include <Blueprint/WidgetLayoutLibrary.h>



void UYWorldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if(WorldUI == nullptr)
		WorldUI = this;
	
	if (OwerPawn == nullptr || UIToWordActor == nullptr )
		return;
	//世界设置到2dUI
	FVector2D Sc2DPos;
	if (UGameplayStatics::ProjectWorldToScreen(OwerPawn->GetController <APlayerController>(), UIToWordActor->GetActorLocation() + WorldOff, Sc2DPos))
	{
		float ViewScale = UWidgetLayoutLibrary::GetViewportScale(WorldUI);

		Sc2DPos /= ViewScale;

		WorldUI->SetRenderTranslation(Sc2DPos);


	}
}
