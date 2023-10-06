// Fill out your copyright notice in the Description page of Project Settings.


#include "Magic_Projectile_Y.h"
#include"Particles\ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include <DrawDebugHelpers.h>
#include <Character_Y.h>
#include "AttributeActorComponent.h"
#include"Components\AudioComponent.h"
#include"Kismet\GameplayStatics.h"


// Sets default values
AMagic_Projectile_Y::AMagic_Projectile_Y()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp_Y");
	RootComponent = SphereComp;
	///////////SphereComponents->SetCollisionObjectType(ECC_worldDynamic);

	SphereComp->SetCollisionProfileName("Projectile");//设置物理碰撞配置文件
	SphereComp->SetSimulatePhysics(true);//模拟物理
	SphereComp->SetGenerateOverlapEvents(true);//是否生成重叠事件
	
	SphereComp->SetEnableGravity(false);//是否启用重力
	//SphereComp->ShapeBodySetup->DefaultInstance.bNotifyRigidBodyCollision = 1;//模拟命中事件
	SphereComp->BodyInstance.bNotifyRigidBodyCollision = true;//模拟命中事件
	SphereComp->SetSphereRadius(7.0f);//设置半径

	ParticleSystemComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystemComp_Y");
	ParticleSystemComp->SetupAttachment(SphereComp);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComp_Y");

	//AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComp_Y");
	//AudioComp->SetupAttachment(RootComponent);

	ProjectileMovementComp->InitialSpeed = 1000.0f;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bInitialVelocityInLocalSpace = true;
	ProjectileMovementComp->ProjectileGravityScale = 0.0f;

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AMagic_Projectile_Y::OnCompBeginOverlap);
	SphereComp->OnComponentHit.AddDynamic(this, &AMagic_Projectile_Y::OnCompHit);
	//AudioComp->OnAudioFinished.AddDynamic(this, &AMagic_Projectile_Y::Destroy);
	
	live = 1;
	Hurt = 20;
}

// Called when the game starts or when spawned
void AMagic_Projectile_Y::BeginPlay()
{
	Super::BeginPlay();
	if(LaunchSound)
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), LaunchSound, GetActorLocation(), (LaunchSound->GetVolumeMultiplier()), (LaunchSound->GetPitchMultiplier()),
		0.0f, (USoundAttenuation*)LaunchSound->AttenuationSettings, (USoundConcurrency*)LaunchSound->SoundConcurrencySettings_DEPRECATED);
}

// Called every frame
void AMagic_Projectile_Y::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMagic_Projectile_Y::OnCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	live = 0;
	DrawDebugString(GetWorld(), SweepResult.ImpactPoint, FString::Printf(TEXT("AMagic_Projectile_Y::OnCompBeginOverlap  OtherActor,%s"), *OtherActor->GetName()), nullptr, FColor::Black, 5.0f, true);
	//SphereComp->SetSimulatePhysics(false);//模拟物理
	//ProjectileMovementComp->StopMovementImmediately();

	//ParticleSystemComp->SetVisibility(false);
	//SetActorEnableCollision(false);
	//AudioComp->Stop();
	//AudioComp->SetSound(NewSoundBase);
	////AudioComp->OnAudioFinished.AddDynamic(this, &AMagic_Projectile_Y::Destroy);
	//AudioComp->Play();
	//
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
	//ProjectileMovementComp->StopMovementImmediately();
	//ProjectileMovementComp->StopSimulating(FHitResult());
	
	//SetActorLocation(SweepResult.Location);
	Destroy();

}

void AMagic_Projectile_Y::OnCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FTimerHandle handle;
	GetWorldTimerManager().SetTimer(handle,this,&AMagic_Projectile_Y::Destroy,0.01f);
	//DrawDebugString(GetWorld(), GetActorLocation(), FString::Printf(TEXT("AMagic_Projectile_Y::UGameplayStatics::PlaySoundAtLocation:")), nullptr, FColor::Red, 5.0f, true);
	HitPoint = Hit.ImpactPoint;
}


void AMagic_Projectile_Y::Destroy()
{	
	if (CollidingSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), CollidingSound, HitPoint,CollidingSound->GetVolumeMultiplier(),CollidingSound->GetPitchMultiplier(),
			0.0f,CollidingSound->AttenuationSettings,CollidingSound->SoundConcurrencySettings_DEPRECATED);
		DrawDebugString(GetWorld(), HitPoint, FString::Printf(TEXT("AMagic_Projectile_Y::UGameplayStatics::PlaySoundAtLocation")), nullptr, FColor::Red, 5.0f, true);
		//UGameplayStatics::PlaySoundAtLocation(GetWorld(), CollidingSound, HitPoint);
	}
		
	this->AActor::Destroy();
	
}

