// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillsActorComponent.h"

#include <Kismet/GameplayStatics.h>
#include <Camera/CameraComponent.h>
#include"Particles\ParticleSystemComponent.h"
#include <PhysicsEngine/RadialForceComponent.h>
#include "Magic_Projectile/BlackHole_Y.h"

// Sets default values for this component's properties
USkillsActorComponent::USkillsActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	end = 300.0f;

	//FTransform Transform;
	

	
	
	// ...
}


// Called when the game starts
void USkillsActorComponent::BeginPlay()
{
	Super::BeginPlay();
	

	// ...
	
}


// Called every frame
void USkillsActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	
	if (A_this_spawnShpere)
	{
		OwnerCameraCompLocation = Cast<UCameraComponent>(GetOwner()->GetComponentByClass(UCameraComponent::StaticClass()))->GetComponentLocation();
		PlayerControllerRotator =Cast<APawn>(	GetOwner() )->GetControlRotation();
		FHitResult hit;
		FVector Endlocation;
		if(CollNmaeFile!=NAME_None)
			GetWorld()->LineTraceSingleByProfile(hit, OwnerCameraCompLocation, OwnerCameraCompLocation + PlayerControllerRotator.Vector() * end, CollNmaeFile);
		
		if (hit.IsValidBlockingHit())
		{
			Endlocation = hit.ImpactPoint;
		}
		else
		{
			Endlocation = OwnerCameraCompLocation + PlayerControllerRotator.Vector() * end;
		}

		
		

		

		A_this_spawnShpere->SetActorLocation(Endlocation);

	}

	// ...
}

void USkillsActorComponent::BlackHole_Spawn()
{
	FTransform Transform;
	PlayerControllerRotator = UGameplayStatics::GetPlayerController(this, 0)->GetControlRotation();
	OwnerCameraCompLocation = Cast<UCameraComponent>(GetOwner()->GetComponentByClass(UCameraComponent::StaticClass()))->GetComponentLocation();


	Transform = FTransform(PlayerControllerRotator, OwnerCameraCompLocation + PlayerControllerRotator.Vector()*end);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<AActor>(Skill_1,Transform,SpawnParameters);

	/*UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), 
		Cast<UParticleSystem>(Skill_1.GetDefaultObject()->GetComponentByClass(UParticleSystem::StaticClass())),Transform); //在世界里 播放粒子特效
	*/
}

void USkillsActorComponent::DrawShpere()
{

	FTransform Transform;

	PlayerControllerRotator = UGameplayStatics::GetPlayerController(this, 0)->GetControlRotation();
	OwnerCameraCompLocation = Cast<UCameraComponent>(GetOwner()->GetComponentByClass(UCameraComponent::StaticClass()))->GetComponentLocation();

	Transform = FTransform(PlayerControllerRotator, OwnerCameraCompLocation + PlayerControllerRotator.Vector() * end);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	A_this_spawnShpere =  GetWorld()->SpawnActor<AActor>(ADrawShpere, Transform, SpawnParameters);
	
	//auto* syc = (Skill_1.GetDefaultObject()->GetComponentByClass(URadialForceComponent::StaticClass()));
	auto* sy = 	(ABlackHole_Y*)(Skill_1.GetDefaultObject());//
	auto* syp = sy->GetParticleSystem();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
		syp, Transform); //在指定位置放指定的粒子特效
}

void USkillsActorComponent::Teleportation()
{

	/*FTransform Transform(Cast<APawn>(	GetOwner() )->GetControlRotation(), GetOwner()->GetActorLocation() + Cast<APawn>(GetOwner())->GetControlRotation().Vector() * 100);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	A_this_ATeleportation = GetWorld()->SpawnActor<AActor>(ATeleportation, Transform, SpawnParameters);*/


	FTimerHandle handle;
	FTimerDelegate Delegate;
	Delegate.BindLambda([&]()->void
		{
			if (A_this_ATeleportation == nullptr)
				return;
			if (!A_this_ATeleportation->IsPendingKill())
			{
				GetOwner()->SetActorLocation(A_this_ATeleportation->GetActorLocation());
				A_this_ATeleportation->Destroy();
				A_this_ATeleportation = nullptr;
			}
		});

	GetOwner()->GetWorldTimerManager().SetTimer(handle, Delegate,2.0f,false);

}

FVector USkillsActorComponent::GetCrosshairend()
{
	PlayerControllerRotator = UGameplayStatics::GetPlayerController(this, 0)->GetControlRotation();
	OwnerCameraCompLocation = Cast<UCameraComponent>(GetOwner()->GetComponentByClass(UCameraComponent::StaticClass()))->GetComponentLocation();
	return OwnerCameraCompLocation + PlayerControllerRotator.Vector() * end;
}

