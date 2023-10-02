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

// Sets default values
ACharacter_Y::ACharacter_Y()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp_Y");
	PlayerCameraComp = CreateDefaultSubobject<UCameraComponent>("PlayerCameraComp_Y");
	SkillsActorComp = CreateDefaultSubobject <USkillsActorComponent>("SkillsActorComp_Y");
	AttributeComp = CreateDefaultSubobject<UAttributeActorComponent>("AttributeComp_Y");

	bUseControllerRotationYaw = false;//��ɫ��Yaw��ʹ����ҿ�����Yaw
	GetCharacterMovement()->bOrientRotationToMovement = true;//�˶����� ��ת
	PlayerCameraComp->SetupAttachment(SpringArmComp);
	SpringArmComp->SetupAttachment(RootComponent);//���ӵ����� ��Ϊ���������
	SpringArmComp->bUsePawnControlRotation = true;

	TimerRate = 0.2f;
	Interactive_Line_end = 100.0f;
}

// Called when the game starts or when spawned
void ACharacter_Y::BeginPlay()
{
	Super::BeginPlay();
	if (CrosshairUI)
	{

		
		CreateWidget(UGameplayStatics::GetPlayerController(this,0), CrosshairUI)->AddToViewport();

	}
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

	//������
	FInputKeyBinding KeyBind(EKeys::R, IE_Pressed);
	KeyBind.bConsumeInput = true;
	KeyBind.bExecuteWhenPaused = false;
	KeyBind.KeyDelegate.BindDelegate(this->SkillsActorComp, &USkillsActorComponent::Teleportation);
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

void ACharacter_Y::magic_Spawn()
{
	PlayAnimMontage(AnimMontage);
	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ACharacter_Y::magic_Spawn_Timer, TimerRate);//���ö�ʱ��
}
void ACharacter_Y::magic_Spawn_Timer()
{

	FVector SpawnLoctaion = GetMesh()->GetSocketLocation("Magic_Spawn");//���ɵ�λ�ã��ڹ�������ϣ�
	FHitResult HitRet;
	FVector Start = PlayerCameraComp->GetComponentLocation();
	FVector end = SkillsActorComp->GetCrosshairend();
	FTransform Transform_Spawn;
	GetWorld()->LineTraceSingleByProfile(HitRet,Start,end, 
		Cast<USphereComponent>(FaSeWu.GetDefaultObject()->GetComponentByClass(USphereComponent::StaticClass()))->GetCollisionProfileName());
	if (HitRet.IsValidBlockingHit())
	{
		end = HitRet.ImpactPoint;

	}

	Transform_Spawn = FTransform((end-SpawnLoctaion).Rotation(), SpawnLoctaion);//���ɵı任
	FActorSpawnParameters spawnParams;//���ɲ���
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<AActor>(FaSeWu, Transform_Spawn, spawnParams);
	GetWorldTimerManager().ClearTimer(TimerHandle);
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
			SkillsActorComp->BlackHole_Spawn();
		}
	}
	i++;
	

}

void ACharacter_Y::Interactive()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	FHitResult HitRet;
	FVector Start;
	FVector end;
	FRotator Rotator;
	ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
	
	Start =	GetPawnViewLocation();//�۾�λ��
	Rotator = GetControlRotation();
	end = Rotator.Vector() * Interactive_Line_end + Start;
	
	GetWorld()->LineTraceSingleByObjectType(HitRet, Start, end, ObjectQueryParams);

	if (HitRet.IsValidBlockingHit())
	{
		if (HitRet.Actor->Implements<UInteractive_Interface>())//�Ƿ�ʵ���˽ӿ�
		{
			auto* Interactive_ = Cast<IInteractive_Interface>(HitRet.Actor);
			Interactive_->Interactive_Implementation();

		}
		
	}
	DrawDebugLine(GetWorld(), Start, end, FColor::Red, false, 5.0f, 0, 10.0f);
}

UAttributeActorComponent* ACharacter_Y::GetAttributeComp()
{
	return AttributeComp;
}

