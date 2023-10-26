// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AICharacter.h"
#include <AIController.h>
#include"Perception\PawnSensingComponent.h"
#include"BehaviorTree\BlackboardComponent.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp_Y");
	PawnSensingComp->bOnlySensePlayers = false;


	TargetActor = TEXT("TargetActor");
	
}

void AAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AAICharacter::OnSeePawnFun);

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




