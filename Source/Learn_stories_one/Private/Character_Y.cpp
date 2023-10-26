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

// Sets default values
ACharacter_Y::ACharacter_Y()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp_Y");
	PlayerCameraComp = CreateDefaultSubobject<UCameraComponent>("PlayerCameraComp_Y");
	SkillsActorComp = CreateDefaultSubobject <USkillsActorComponent>("SkillsActorComp_Y");
	AttributeComp = CreateDefaultSubobject<UAttributeActorComponent>("AttributeComp_Y");

	bUseControllerRotationYaw = false;//角色的Yaw不使用玩家控器的Yaw
	GetCharacterMovement()->bOrientRotationToMovement = true;//运动朝向 旋转
	PlayerCameraComp->SetupAttachment(SpringArmComp);
	SpringArmComp->SetupAttachment(RootComponent);//附加到根上 成为根的子组件
	SpringArmComp->bUsePawnControlRotation = true;

	TimerRate = 0.2f;
	Interactive_Line_end = 100.0f;
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

	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacter_Y::MoveForward);//绑定轴映射前进
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacter_Y::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ACharacter_Y::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacter_Y::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter_Y::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter_Y::StopJump);
	PlayerInputComponent->BindAction("Projectile_Spawn", IE_Pressed, this, &ACharacter_Y::magic_Spawn);

	//单键绑定
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

void ACharacter_Y::magic_Spawn()
{
	PlayAnimMontage(AnimMontage);
	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ACharacter_Y::magic_Spawn_Timer, TimerRate);//设置定时器
}
void ACharacter_Y::magic_Spawn_Timer()
{

	FVector SpawnLoctaion = GetMesh()->GetSocketLocation("Magic_Spawn");//生成的位置（在骨骼插槽上）
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

	Transform_Spawn = FTransform((end-SpawnLoctaion).Rotation(), SpawnLoctaion);//生成的变换
	FActorSpawnParameters spawnParams;//生成参数
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	spawnParams.Owner = this;
	spawnParams.Instigator = this;
	//spawnParams.Name = TEXT("gj");
	GetWorld()->SpawnActor<AActor>(FaSeWu, Transform_Spawn, spawnParams);//->SetOwner(this);
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
	
	Start =	GetPawnViewLocation();//眼睛位置
	Rotator = GetControlRotation();
	end = Rotator.Vector() * Interactive_Line_end + Start;
	
	GetWorld()->LineTraceSingleByObjectType(HitRet, Start, end, ObjectQueryParams);

	if (HitRet.IsValidBlockingHit())
	{
		if (HitRet.Actor->Implements<UInteractive_Interface>())//是否实现了接口
		{
			auto* Interactive_ = Cast<IInteractive_Interface>(HitRet.Actor);
			Interactive_->Execute_Interactive(HitRet.Actor.Get(),this);

		}
		
	}
	DrawDebugLine(GetWorld(), Start, end, FColor::Red, false, 5.0f, 0, 10.0f);
}

UAttributeActorComponent* ACharacter_Y::GetAttributeComp()
{
	return AttributeComp;
}

void ACharacter_Y::OnBldVeChanged(AActor* Actor, UAttributeActorComponent* AttributeActorComp, float Newblood_volume, float DelVal)
{
	if (Newblood_volume <= 0.0f && DelVal <= 0.0f)
	{
		auto* PC = 	Cast<APlayerController>(GetController());
		DisableInput(PC);//禁用输入
		//GetCapsuleComponent()->colse
		//SetActorEnableCollision(false);//允许为整个Actor启用/禁用碰撞
		
		GetMesh()->SetCollisionProfileName("Ragdoll");
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetMesh()->SetAllBodiesSimulatePhysics(true);
		GetMesh()->SetDrawDebugSkeleton(true);
		//SetActorRelativeTransform(GetMesh()->GetComponentTransform());

	}

}

void ACharacter_Y::OnCapsuleCompOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetOwner() == this)
	{

		return;
	}
	if (ensureMsgf(CameraShake, TEXT("erro 相机抖动为空.")))
	{

	//镜头抖动
		GetController<APlayerController>()->ClientPlayCameraShake(CameraShake);
		//可触发式延迟
		UKismetSystemLibrary::RetriggerableDelay(this, 0.2f, FLatentActionInfo(0,0,TEXT("ClientStopCameraShake"),this));
	}
	

}

void ACharacter_Y::ClientStopCameraShake()
{
		//关闭镜头抖动
		GetController<APlayerController>()->ClientStopCameraShake(CameraShake);
}

