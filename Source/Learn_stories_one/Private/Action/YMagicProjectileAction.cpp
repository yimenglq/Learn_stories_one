// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/YMagicProjectileAction.h"
#include"Animation\AnimMontage.h"
#include"GameFramework\Actor.h"
#include"GameFramework\Character.h"
#include "Character_Y.h"
#include"Camera\CameraComponent.h"
#include "SkillsActorComponent.h"
#include"Components\SphereComponent.h"


UYMagicProjectileAction::UYMagicProjectileAction()
{
	TimerRate = 2.0f;
	SocketName = NAME_None;//"Magic_Spawn"
}

void UYMagicProjectileAction::StartAction_Implementation(AActor* IncitingActor)
{
	UE_LOG(LogTemp, Log, TEXT("UYMagicProjectileAction::StartAction_Implementation"), *GetNameSafe(this));
	ACharacter_Y* IncitingACharacter = Cast<ACharacter_Y>(IncitingActor);
	if (ensure(	AnimMontage) && IncitingACharacter)
	{
		IncitingACharacter->PlayAnimMontage(AnimMontage);
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUObject(this, &UYMagicProjectileAction::MagicProjectileSpawn, IncitingACharacter);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle,TimerDelegate, TimerRate,false);//设置定时器
	}
}


void UYMagicProjectileAction::StopAction_Implementation(AActor* IncitingActor)
{
	UE_LOG(LogTemp, Log, TEXT("UYMagicProjectileAction::StartAction_Implementation"), *GetNameSafe(this));
}



void UYMagicProjectileAction::MagicProjectileSpawn(ACharacter_Y* IncitingACharacter)
{
	
	
	FHitResult HitRet;
	FVector Start{0,0,0};
	if (auto * comp = IncitingACharacter->GetCameraComponent())
	{
		Start = comp->GetComponentLocation();
	}
	else
	{
		FRotator n;
		IncitingACharacter->GetActorEyesViewPoint(Start , n);
	}

	FVector end = IncitingACharacter->GetControlRotation().Vector() * Range.X + IncitingACharacter->GetActorLocation();
	FTransform Transform_Spawn;
	GetWorld()->LineTraceSingleByProfile(HitRet, Start, end,
		Cast<USphereComponent>(this->MagicProjectileClass.GetDefaultObject()->GetComponentByClass(USphereComponent::StaticClass()) ) ->GetCollisionProfileName());
	if (HitRet.IsValidBlockingHit())
	{
		end = HitRet.ImpactPoint;

	}
	FVector SpawnLoctaion{ 0,0,0 };
	if (SocketName == NAME_None)
	{
		SpawnLoctaion = end;
	}
	else
	{
		SpawnLoctaion = IncitingACharacter->GetMesh()->GetSocketLocation(SocketName);//生成的位置（在骨骼插槽上）
	}
	Transform_Spawn = FTransform((end - SpawnLoctaion).Rotation(), SpawnLoctaion);//生成的变换
	FActorSpawnParameters spawnParams;//生成参数
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	spawnParams.Owner = IncitingACharacter;
	spawnParams.Instigator = IncitingACharacter;
	
	SpawnMagicProjectile = GetWorld()->SpawnActor<AActor>(this->MagicProjectileClass, Transform_Spawn, spawnParams);//->SetOwner(this);
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

}

AActor* UYMagicProjectileAction::GetSpawnMagicProjectile() const
{
	return SpawnMagicProjectile;
}

void UYMagicProjectileAction::Action(UObject** out)
{ 
	*out = GetSpawnMagicProjectile();
}
