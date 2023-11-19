// Fill out your copyright notice in the Description page of Project Settings.


#include "Explosive_Y.h"

#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Magic_Projectile/Magic_Projectile_Y.h"

// Sets default values
AExplosive_Y::AExplosive_Y()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp_Y");
	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp_Y");
	RootComponent =	StaticMeshComp;

	ForceComp->SetupAttachment(RootComponent);


	StaticMeshComp->SetSimulatePhysics(true);//模拟物理
	StaticMeshComp->OnComponentHit.AddDynamic(this, &AExplosive_Y::OnCompHit);

	ForceComp->ImpulseStrength = 1000.0f;
	ForceComp->Radius = 100.0f;

}

// Called when the game starts or when spawned
void AExplosive_Y::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExplosive_Y::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExplosive_Y::OnCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(Cast<AMagic_Projectile_Y>(OtherActor))
		ForceComp->FireImpulse();//发射径向力

}

