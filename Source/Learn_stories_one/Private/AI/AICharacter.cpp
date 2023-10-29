// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AICharacter.h"
#include <AIController.h>
#include"Perception\PawnSensingComponent.h"
#include"BehaviorTree\BlackboardComponent.h"
#include"Components\CapsuleComponent.h"
#include <Magic_Projectile_Y.h>
#include <Kismet/GameplayStatics.h>
#include"Blueprint\UserWidget.h"
#include "AttributeActorComponent.h"
#include "AI_UserWidget.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp_Y");
	c_AttributeActorComp = CreateDefaultSubobject <UAttributeActorComponent>("AttributeActorComp_Y");

	
	PawnSensingComp->bOnlySensePlayers = false;
	c_AttributeActorComp->ReviseBlood_volume(100.f);

	TargetActor = TEXT("TargetActor");
	c_UIWorldOffetValue = { 0,0,0 };
	c_AIHitFlashSpeed = 8.0f;
	/*OnActorBeginOverlap.AddDynamic(this, &AAICharacter::OnActorBeginOverlapFun);*/
}

void AAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AAICharacter::OnSeePawnFun);

	this->GetCapsuleComponent()->OnComponentBeginOverlap.AddUniqueDynamic(this, &AAICharacter::OnComponentBeginOverlapFun);

	c_AttributeActorComp->OnBlood_volume_Changed.AddUniqueDynamic(this, &AAICharacter::OnBlood_volume_ChangedFun);

	OnDestroyed.AddUniqueDynamic(this, &AAICharacter::OnDestroyedFun);//显示销毁Actor时调用
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAICharacter::OnSeePawnFun(APawn* Pawn)
{
	AAIController* AIConl = Cast<AAIController>(GetController());
	
	if (AIConl)
	{
		
		UBlackboardComponent* BlackboardComp = AIConl->GetBlackboardComponent();
		BlackboardComp->SetValueAsObject(TargetActor,Pawn);
	}


}

void AAICharacter::OnComponentBeginOverlapFun(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	return;
	/*AMagic_Projectile_Y * AMagicActor = Cast<AMagic_Projectile_Y>(OtherActor);
	if (AMagicActor)
	{
		if (ensure(c_AIwidgetClass))
		{
			c_AIwidget = CreateWidget(this, c_AIwidgetClass, TEXT("XUETIAO"));


			FVector2D  UI_location2D = { 0,0 };
			UGameplayStatics::ProjectWorldToScreen(UGameplayStatics::GetPlayerController(this, 0), GetActorLocation(), UI_location2D);
			c_AIwidget->SetRenderTranslation(UI_location2D);
			
		}
			


	}*/
	
}

void AAICharacter::OnBlood_volume_ChangedFun(AActor* Actor, UAttributeActorComponent* AttributeActorComp, float Newblood_volume, float DelVal)
{
	if (ensure(c_BloodUI)&& (c_BloodUIIniscte ==nullptr))
	{
		c_BloodUIIniscte = CreateWidget<UAI_UserWidget>(GetWorld(), c_BloodUI);
		c_BloodUIIniscte->c_AttachedActor = this;
		c_BloodUIIniscte->c_WorldOffetValue = c_UIWorldOffetValue;
		c_BloodUIIniscte->c_OldBlood = Newblood_volume - DelVal;
		c_BloodUIIniscte->AddToViewport();
	}

	

}

void AAICharacter::OnDestroyedFun(AActor* DestroyedActor)
{

	if (c_BloodUIIniscte)
	{
		c_BloodUIIniscte->RemoveFromParent();
		c_BloodUIIniscte = nullptr;

		
	}

}


