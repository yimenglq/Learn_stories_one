// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole_Y.h"
#include"Particles\ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include <DrawDebugHelpers.h>

ABlackHole_Y::ABlackHole_Y():Super::AMagic_Projectile_Y()
{
	ProjectileMovementComp->InitialSpeed = 500.0f;
	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp_Y");
	ForceComp->SetupAttachment(RootComponent);
	
	ForceComp->Radius = 50.0f;
	ForceComp->ImpulseStrength = -10000.0f;



}

void ABlackHole_Y::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	ForceComp->FireImpulse();

}



UParticleSystem* ABlackHole_Y::GetParticleSystem()
{
	return InParticleSystem;
}

void ABlackHole_Y::OnCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	DrawDebugString(GetWorld(), SweepResult.ImpactPoint, FString::Printf(TEXT("ABlackHole_Y::OnCompBeginOverlap  OtherActor,%s"), *OtherActor->GetName()), nullptr, FColor::Black, 2.0f, true);
	
	if (AMagic_Projectile_Y* actor = Cast<AMagic_Projectile_Y>(OtherActor))
	{
		actor->Destroy();

	}
	else
	{
		OtherActor->Destroy();

	}
		
}


