// Fill out your copyright notice in the Description page of Project Settings.


#include "Magic_Projectile_Y.h"
#include"Particles\ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include <DrawDebugHelpers.h>
#include <Character_Y.h>
#include "AttributeActorComponent.h"


// Sets default values
AMagic_Projectile_Y::AMagic_Projectile_Y()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp_Y");
	RootComponent = SphereComp;
	///////////SphereComponents->SetCollisionObjectType(ECC_worldDynamic);

	SphereComp->SetCollisionProfileName("Projectile");//����������ײ�����ļ�
	SphereComp->SetSimulatePhysics(true);//ģ������
	SphereComp->SetGenerateOverlapEvents(true);//�Ƿ������ص��¼�
	
	SphereComp->SetEnableGravity(false);//�Ƿ���������
	//SphereComp->ShapeBodySetup->DefaultInstance.bNotifyRigidBodyCollision = 1;//ģ�������¼�
	SphereComp->BodyInstance.bNotifyRigidBodyCollision = true;//ģ�������¼�

	ParticleSystemComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystemComp_Y");
	ParticleSystemComp->SetupAttachment(SphereComp);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComp_Y");


	ProjectileMovementComp->InitialSpeed = 1000.0f;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bInitialVelocityInLocalSpace = true;
	ProjectileMovementComp->ProjectileGravityScale = 0.0f;

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AMagic_Projectile_Y::OnCompBeginOverlap);
	SphereComp->OnComponentHit.AddDynamic(this, &AMagic_Projectile_Y::OnCompHit);
	live = 1;
	Hurt = 20;
}

// Called when the game starts or when spawned
void AMagic_Projectile_Y::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMagic_Projectile_Y::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMagic_Projectile_Y::OnCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	DrawDebugString(GetWorld(), SweepResult.ImpactPoint, FString::Printf(TEXT("AMagic_Projectile_Y::OnCompBeginOverlap  OtherActor,%s"), *OtherActor->GetName()), nullptr, FColor::Black, 5.0f, true);

	if (auto* Character = Cast<ACharacter_Y>(OtherActor))
	{
		UAttributeActorComponent* Attribute = 	Character->GetAttributeComp();
		Attribute->ReviseBlood_volume(-Hurt);

	}
	else
	if (UAttributeActorComponent * Attribute = Cast < UAttributeActorComponent>(OtherActor->GetComponentByClass(UAttributeActorComponent::StaticClass())))
	{
		Attribute->ReviseBlood_volume(-Hurt);

	}

	Destroy();

}

void AMagic_Projectile_Y::OnCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FTimerHandle handle;
	GetWorldTimerManager().SetTimer(handle,this,&AMagic_Projectile_Y::Destroy,0.01f);

}


void AMagic_Projectile_Y::Destroy()
{	
	live = 0;
	this->AActor::Destroy();
	
}

