// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactive/InteractiveComponent.h"
#include <Interactive_Interface.h>
#include <DrawDebugHelpers.h>
#include <Kismet/GameplayStatics.h>
#include <Blueprint/WidgetLayoutLibrary.h>
#include"UI\YWorldUserWidget.h"


//UYWorldUserWidget* UInteractiveComponent::InteractiveUI = nullptr;
// Sets default values for this component's properties
UInteractiveComponent::UInteractiveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractiveComponent::BeginPlay()
{
	Super::BeginPlay();

	if (InteractiveUI == nullptr && ensure(InteractiveUIClss))
	{
		InteractiveUI = CreateWidget<UYWorldUserWidget>(GetWorld(), InteractiveUIClss);
	
		if (InteractiveUI)
		{
			
			InteractiveUI->OwerPawn = OwerPawn;
			InteractiveUI->AddToViewport();

		}
	}
	// ...
	
}


// Called every frame
void UInteractiveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FindActorIsInteractive();
	// ...
}

bool UInteractiveComponent::FindActorIsInteractive()
{
	bool ret = true;
	if (InteractiveUI == nullptr)
	{
		return false;
	}

	FCollisionObjectQueryParams ObjectQueryParams;
	
	FVector Start;
	FVector end;
	FRotator Rotator;
	for (ECollisionChannel CollisionChannel : CollisionChannels)
	{

	
		ObjectQueryParams.AddObjectTypesToQuery(CollisionChannel);
	}
	Start = OwerPawn->GetPawnViewLocation();//眼睛位置
	Rotator = OwerPawn->GetControlRotation();
	if (auto* playeConl = OwerPawn->GetController <APlayerController>())
	{
		FVector loc = playeConl->PlayerCameraManager->GetCameraLocation();
		//FVector lob = playeConl->PlayerCameraManager->GetTransformComponent()->GetComponentLocation();
		end = Rotator.Vector() * Interactive_Line_end + loc;

	}
	else
	{
		return false;
	}
	GetWorld()->LineTraceSingleByObjectType(HitRet, Start, end, ObjectQueryParams);

	if (HitRet.IsValidBlockingHit())
	{
		if (HitRet.Actor->Implements<UInteractive_Interface>())//是否实现了接口
		{
			HitActor = HitRet.Actor.Get();

		
			////世界设置到2dUI
			//	FVector2D Sc2DPos;
			//	if (UGameplayStatics::ProjectWorldToScreen(OwerPawn->GetController <APlayerController>(), HitRet.Actor->GetActorLocation(), Sc2DPos))
			//	{
			//		float ViewScale =	UWidgetLayoutLibrary::GetViewportScale(InteractiveUI);

			//		Sc2DPos /=	ViewScale;

			//		InteractiveUI->SetRenderTranslation(Sc2DPos);
			//	

			//	}
				InteractiveUI->OwerPawn = OwerPawn;
				InteractiveUI->UIToWordActor = HitRet.Actor.Get();
				
				InteractiveUI->SetVisibility(ESlateVisibility::Visible);
				DrawDebugLine(GetWorld(), Start, end, FColor::Red, false, 5.0f, 0, 10.0f);
		}
		else
		{
			InteractiveUI->OwerPawn = nullptr;
			InteractiveUI->UIToWordActor = nullptr;
			HitActor = nullptr;
		}
	}
	else
	{
		if(InteractiveUI->GetVisibility() != ESlateVisibility::Collapsed)
			InteractiveUI->SetVisibility(ESlateVisibility::Collapsed);
		HitActor = nullptr;
	}
	
	
//DrawDebugLine(GetWorld(), Start, end, FColor::Red, false, 5.0f, 0, 10.0f);

	return ret;
}

void UInteractiveComponent::StartInteractive()
{
	if (!HitActor)
	{
		return;
	}
	auto* Interactive_ = Cast<IInteractive_Interface>(HitActor);
	Interactive_->Execute_Interactive(HitActor, OwerPawn);
}




