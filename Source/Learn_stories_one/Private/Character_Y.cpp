// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Y.h"
#include"Camera\CameraComponent.h"
#include"GameFramework\SpringArmComponent.h"
#include"GameFramework\CharacterMovementComponent.h"
#include"GameFramework\PlayerInput.h"
#include <Kismet/GameplayStatics.h>
#include "SkillsActorComponent.h"
#include <Interactive_Interface.h>
#include <DrawDebugHelpers.h>
#include"Blueprint\UserWidget.h"
#include "AttributeActorComponent.h"
#include <Components/SphereComponent.h>
#include"Components\CapsuleComponent.h"
#include <Camera/CameraShakeSourceComponent.h>
#include "GameMode/YGameModeBase.h"
#include "Action/ActionActorComp.h"
#include"Action\YAction.h"
#include"Interactive\InteractiveComponent.h"



// Sets default values
ACharacter_Y::ACharacter_Y()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp_Y");
	PlayerCameraComp = CreateDefaultSubobject<UCameraComponent>("PlayerCameraComp_Y");
	SkillsActorComp = CreateDefaultSubobject <USkillsActorComponent>("SkillsActorComp_Y");
	AttributeComp = CreateDefaultSubobject<UAttributeActorComponent>("AttributeComp_Y");
	ActionActorComp = CreateDefaultSubobject<UActionActorComp>("ActionActorComp_Y");
	InteractiveComp = CreateDefaultSubobject<UInteractiveComponent>("InteractiveComp_Y");

	
	bUseControllerRotationYaw = false;//��ɫ��Yaw��ʹ����ҿ�����Yaw
	GetCharacterMovement()->bOrientRotationToMovement = true;//�˶����� ��ת
	PlayerCameraComp->SetupAttachment(SpringArmComp);
	SpringArmComp->SetupAttachment(RootComponent);//���ӵ����� ��Ϊ���������
	SpringArmComp->bUsePawnControlRotation = true;

	TimerRate = 0.2f;

}

void ACharacter_Y::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComp->OnBlood_volume_Changed.AddDynamic(this, &ACharacter_Y::OnBldVeChanged);
	this->GetCapsuleComponent()->OnComponentBeginOverlap.AddUniqueDynamic(this, &ACharacter_Y::OnCapsuleCompOverlap);
}

// Called when the game starts or when spawned
void ACharacter_Y::BeginPlay()
{
	Super::BeginPlay();
	InteractiveComp->OwerPawn = this;
	/*if (CrosshairUI)
	{
		
		if (APlayerController* PlayerController = GetController<APlayerController>())
		{
			AYGameModeBase* GameMode =Cast<AYGameModeBase>(	UGameplayStatics::GetGameMode(this));
			if (!GameMode)
				return;
			UUserWidget* Widget = GameMode->IsControllerAttWidget(PlayerController);
			if (Widget != nullptr)
			{

				
				return;
			}
			Widget = CreateWidget(PlayerController, CrosshairUI);
			Widget->AddToViewport();
			GameMode->AddControllerAttWidget(PlayerController, Widget);

		}
			

	}*/
}

// Called every frame
void ACharacter_Y::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacter_Y::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacter_Y::MoveForward);//����ӳ��ǰ��
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacter_Y::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ACharacter_Y::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacter_Y::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter_Y::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter_Y::StopJump);
	PlayerInputComponent->BindAction("Projectile_Spawn", IE_Pressed, this, &ACharacter_Y::magic_Spawn);
	PlayerInputComponent->BindAction("Projectile_Spawn", IE_Released, this, &ACharacter_Y::magic_Spawned);

	FName Sprint("Sprint");
	FInputActionKeyMapping SprintKeyMap(Sprint, EKeys::LeftShift);
	UGameplayStatics::GetPlayerController(this, 0)->PlayerInput->AddActionMapping(SprintKeyMap);
	PlayerInputComponent->BindAction(Sprint, IE_Pressed, this, &ACharacter_Y::SatrtSprint);
	PlayerInputComponent->BindAction(Sprint, IE_Released, this, &ACharacter_Y::StopSprint);




	//������
	FInputKeyBinding KeyBind(EKeys::R, IE_Pressed);
	KeyBind.bConsumeInput = true;
	KeyBind.bExecuteWhenPaused = false;
	KeyBind.KeyDelegate.BindDelegate(this, &ACharacter_Y::Teleportation);
	PlayerInputComponent->KeyBindings.Add(KeyBind);
	//end
	
	//
	FName name = "BlackHole_Spawn";
	FInputActionKeyMapping ActionKeyMap(name, EKeys::Q);
	UGameplayStatics::GetPlayerController(this, 0)->PlayerInput->AddActionMapping(ActionKeyMap);
	PlayerInputComponent->BindAction(name, IE_Pressed, this,&ACharacter_Y::BlackHole);
	PlayerInputComponent->BindAction(name, IE_Released, this, &ACharacter_Y::BlackHole);




	//������  ����
	FInputKeyBinding KeyBind_Interactive(EKeys::E, IE_Pressed);
	KeyBind_Interactive.bConsumeInput = true;
	KeyBind_Interactive.bExecuteWhenPaused = false;
	KeyBind_Interactive.KeyDelegate.BindDelegate(this, &ACharacter_Y::Interactive);
	PlayerInputComponent->KeyBindings.Add(KeyBind_Interactive);

}


void ACharacter_Y::MoveForward(float Value)
{
	/*�ظ��������緽��ʸ����ͨ����һ��������˶����룬����ScaleValue�����š��������ֵ< 0�����ƶ������෴��
	 * ���� Pawn �಻���Զ�Ӧ���ƶ������û��� Tick �¼���ִ�д˲�����Character �� DefaultPawn ��������Զ���������벢�ƶ���
	 
	 @param WorldDirection		Direction in world space to apply input  
	 ����ռ���Ӧ������ķ���
	 * @param ScaleValue		Scale to apply to input. This can be used for analog input, ie a value of 0.5 applies half the normal value, while -1.0 would reverse the direction.
	 * ������Ӧ�������롣�������ģ�����룬��ֵ 0.5 Ӧ������ֵ��һ�룬�� -1.0 ����ת����
	 * @param bForce			If true always add the input, ignoring the result of IsMoveInputIgnored().
	 * ���Ϊ true����ʼ��������룬���� IsMoveInputIgnored���� �Ľ����
	 */
	AddMovementInput(FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X), Value);

	//AddMovementInput(GetActorForwardVector(), Value);
}
void ACharacter_Y::MoveRight(float Value)
{
	AddMovementInput(FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y), Value);

	//AddMovementInput(GetActorRightVector(), Value);
}

void ACharacter_Y::StartJump()
{
	bPressedJump = true;
}
void ACharacter_Y::StopJump()
{
	bPressedJump = false;
}

void ACharacter_Y::SatrtSprint()
{
	ActionActorComp->StartAction(this, "Sprint");
}

void ACharacter_Y::StopSprint()
{
	ActionActorComp->StopAction(this, "Sprint");
}

void ACharacter_Y::magic_Spawn()
{


	ActionActorComp->StartAction(this, "Magic_Projectile");
}
void ACharacter_Y::magic_Spawned()
{
	ActionActorComp->StopAction(this, "Magic_Projectile");
}
void ACharacter_Y::Teleportation()
{
	ActionActorComp->StartAction(this, "Teleportation");

	FTimerHandle TimerHand;
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([this]()->void
		{
			if (auto* Action = ActionActorComp->FindAction("Teleportation"))
				{
					Action->Action( (UObject**) & (this->SkillsActorComp->A_this_ATeleportation));
					this->SkillsActorComp->Teleportation();

				}
		});
	GetWorld()->GetTimerManager().SetTimer(TimerHand, TimerDelegate,1.0f,false);
	ActionActorComp->StopAction(this, "Teleportation");
	
	

}


void ACharacter_Y::BlackHole()
{
	


	static int i = 0;
	if (!(i%2))
	{
		SkillsActorComp->DrawShpere();


	}
	else
	{
		
		if (SkillsActorComp->A_this_spawnShpere)
		{

		
			if (!SkillsActorComp->A_this_spawnShpere->IsPendingKill())
			{
				SkillsActorComp->A_this_spawnShpere->Destroy();
				SkillsActorComp->A_this_spawnShpere = nullptr;
			}	
			ActionActorComp->StartAction(this, "SpawnBlackHole");
			ActionActorComp->StopAction(this, "SpawnBlackHole");
		}
	}
	i++;
	
	

}

void ACharacter_Y::Interactive()
{
	Server_Interactive();

}

void ACharacter_Y::Server_Interactive_Implementation()
{
	InteractiveComp->StartInteractive();

}



UAttributeActorComponent* ACharacter_Y::GetAttributeComp()
{
	return AttributeComp;
}

UCameraComponent* ACharacter_Y::GetCameraComponent()
{
	return PlayerCameraComp;
}

UActionActorComp* ACharacter_Y::GetActionActorComp() const
{
	return ActionActorComp;
}

void ACharacter_Y::OnBldVeChanged(AActor* Actor, UAttributeActorComponent* AttributeActorComp, float Newblood_volume, float DelVal)
{
	UE_LOG(LogTemp, Warning, TEXT("ACharacter_Y::OnBldVeChanged"))
	if (Newblood_volume <= 0.0f && DelVal <= 0.0f)
	{
		
			GetMesh()->SetCollisionProfileName("Ragdoll");
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
			GetCapsuleComponent()->SetSimulatePhysics(true);
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			//GetMesh()->SetDrawDebugSkeleton(true);
			auto* PC = 	Cast<APlayerController>(GetController());
		if (PC)
		{
			PC->UnPossess();
			DisableInput(PC);//��������
			
		
			GetWorld()->GetAuthGameMode<AYGameModeBase>()->RebirthRules(PC);
			
			//GetMovementComponent()->StopMovementImmediately();
		}
	}

}

void ACharacter_Y::OnCapsuleCompOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp,Warning,TEXT("ACharacter_Y::OnCapsuleCompOverlap"))
	if (OtherActor->GetOwner() == this)
	{

		return;
	}
	if (ensureMsgf(CameraShake, TEXT("erro �������Ϊ��.")))
	{

	//��ͷ����
		if (auto* PlayerController = GetController<APlayerController>())
		{


			PlayerController -> ClientPlayCameraShake(CameraShake);
		
		//�ɴ���ʽ�ӳ�
		UKismetSystemLibrary::RetriggerableDelay(this, 0.2f, FLatentActionInfo(0,0,TEXT("ClientStopCameraShake"),this));
		}
	}

}

void ACharacter_Y::ClientStopCameraShake()
{
		//�رվ�ͷ����
		GetController<APlayerController>()->ClientStopCameraShake(CameraShake);
}

