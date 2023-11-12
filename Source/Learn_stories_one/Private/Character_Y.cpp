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

	
	bUseControllerRotationYaw = false;//角色的Yaw不使用玩家控器的Yaw
	GetCharacterMovement()->bOrientRotationToMovement = true;//运动朝向 旋转
	PlayerCameraComp->SetupAttachment(SpringArmComp);
	SpringArmComp->SetupAttachment(RootComponent);//附加到根上 成为根的子组件
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

	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacter_Y::MoveForward);//绑定轴映射前进
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




	//单键绑定
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




	//单键绑定  交互
	FInputKeyBinding KeyBind_Interactive(EKeys::E, IE_Pressed);
	KeyBind_Interactive.bConsumeInput = true;
	KeyBind_Interactive.bExecuteWhenPaused = false;
	KeyBind_Interactive.KeyDelegate.BindDelegate(this, &ACharacter_Y::Interactive);
	PlayerInputComponent->KeyBindings.Add(KeyBind_Interactive);

}


void ACharacter_Y::MoveForward(float Value)
{
	/*沿给定的世界方向矢量（通常归一化）添加运动输入，按“ScaleValue”缩放。如果比例值< 0，则移动方向相反。
	 * 基础 Pawn 类不会自动应用移动，由用户在 Tick 事件中执行此操作。Character 和 DefaultPawn 等子类会自动处理此输入并移动。
	 
	 @param WorldDirection		Direction in world space to apply input  
	 世界空间中应用输入的方向
	 * @param ScaleValue		Scale to apply to input. This can be used for analog input, ie a value of 0.5 applies half the normal value, while -1.0 would reverse the direction.
	 * 缩放以应用于输入。这可用于模拟输入，即值 0.5 应用正常值的一半，而 -1.0 将反转方向。
	 * @param bForce			If true always add the input, ignoring the result of IsMoveInputIgnored().
	 * 如果为 true，则始终添加输入，忽略 IsMoveInputIgnored（） 的结果。
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
			DisableInput(PC);//禁用输入
			
		
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
	if (ensureMsgf(CameraShake, TEXT("erro 相机抖动为空.")))
	{

	//镜头抖动
		if (auto* PlayerController = GetController<APlayerController>())
		{


			PlayerController -> ClientPlayCameraShake(CameraShake);
		
		//可触发式延迟
		UKismetSystemLibrary::RetriggerableDelay(this, 0.2f, FLatentActionInfo(0,0,TEXT("ClientStopCameraShake"),this));
		}
	}

}

void ACharacter_Y::ClientStopCameraShake()
{
		//关闭镜头抖动
		GetController<APlayerController>()->ClientStopCameraShake(CameraShake);
}

