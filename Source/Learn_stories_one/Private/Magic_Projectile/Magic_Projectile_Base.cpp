// Fill out your copyright notice in the Description page of Project Settings.


#include "Magic_Projectile/Magic_Projectile_Base.h"
#include"Particles\ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AMagic_Projectile_Base::AMagic_Projectile_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp_Y");
	RootComponent = SphereComp;
	ParticleSystemComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystemComp_Y");
	ParticleSystemComp->SetupAttachment(SphereComp);
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComp_Y");
	

	ProjectileMovementComp->InitialSpeed = 1000.0f;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bInitialVelocityInLocalSpace = true;
	ProjectileMovementComp->ProjectileGravityScale = 0.0f;


	SetReplicates(true);//ÔÚÍøÂç¼ä¸´ÖÆ
}

// Called when the game starts or when spawned
void AMagic_Projectile_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMagic_Projectile_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

