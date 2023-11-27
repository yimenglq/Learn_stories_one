// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeActorComponent.h"
#include <Net/UnrealNetwork.h>

// Sets default values for this component's properties
UAttributeActorComponent::UAttributeActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	
	blood_volume =  Maxblood = 100;
	

	//SetIsReplicated(true);
	SetIsReplicatedByDefault(true);
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

void UAttributeActorComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UAttributeActorComponent, blood_volume);
	DOREPLIFETIME(UAttributeActorComponent, Maxblood);
	//DOREPLIFETIME_CONDITION(UAttributeActorComponent, Maxblood, COND_InitialOnly);
}
void UAttributeActorComponent::MulticastBoloodChanged_Implementation(AActor* InstigatorActor, float NewBlood, float Delta)
{

	OnBlood_volume_Changed.Broadcast(InstigatorActor, this, NewBlood, Delta);
}

void UAttributeActorComponent::ServerBloodChanged_Implementation(AActor* InstigatorActor, float NewBlood, float Delta)
{
	GEngine->AddOnScreenDebugMessage(0, 100.0f, FColor::Red, TEXT(" UAttributeActorComponent::ServerValidate_Implementation"));
	if (auto * comp = Cast<UAttributeActorComponent>(InstigatorActor->GetComponentByClass(UAttributeActorComponent::StaticClass())))
	{	
		if (comp->blood_volume != 0)
		{
			
			comp->MulticastBoloodChanged(InstigatorActor, comp->blood_volume, 0);
		}

	}
		
}

void UAttributeActorComponent::ReviseBlood_volume(int InVal)
{
	if (blood_volume <= 0)
		return;
		blood_volume += InVal;
		blood_volume > Maxblood ? blood_volume = Maxblood : NULL;
		//OnBlood_volume_Changed.Broadcast(GetOwner(),this, blood_volume, InVal);
	if(!GetOwner()->HasAuthority())
		if (blood_volume <= 0)
		{
		   Cast<UAttributeActorComponent>( GetWorld()->GetFirstLocalPlayerFromController()->PlayerController\
			   ->GetPawn()->GetComponentByClass( UAttributeActorComponent::StaticClass() ) )\
			   -> ServerBloodChanged(GetOwner(), blood_volume, InVal );
			return;
		}
		
		MulticastBoloodChanged(GetOwner(), blood_volume, InVal);
		
		
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

void UAttributeActorComponent::SetBloodVolume(int InBloodVal)
{
	blood_volume = InBloodVal;

}

bool UAttributeActorComponent::IsAlive()
{
	return blood_volume > 0.0f;
}

