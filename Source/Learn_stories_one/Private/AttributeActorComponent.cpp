// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeActorComponent.h"

// Sets default values for this component's properties
UAttributeActorComponent::UAttributeActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	
	blood_volume =  Maxblood = 100;
	
	// ...
}


// Called when the game starts
void UAttributeActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAttributeActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



void UAttributeActorComponent::ReviseBlood_volume(int InVal)
{
	blood_volume += InVal;
	blood_volume > Maxblood ? blood_volume = Maxblood : NULL;
	OnBlood_volume_Changed.Broadcast(GetOwner(),this, blood_volume, InVal);
}

//Static Function  start
UAttributeActorComponent* UAttributeActorComponent::GetAttributeActorComponent(AActor* InActor)
{
	if (InActor)
	{
		return Cast<UAttributeActorComponent>(InActor->GetComponentByClass(UAttributeActorComponent::StaticClass()));
	}

	return nullptr;
}


//Static Function end

int UAttributeActorComponent::GetBlood_volume()
{
	return blood_volume;
}

void UAttributeActorComponent::GetBlood_volume(int& OutVal)
{
	OutVal = blood_volume;
	
}

bool UAttributeActorComponent::IsAlive()
{
	return blood_volume > 0.0f;
}

