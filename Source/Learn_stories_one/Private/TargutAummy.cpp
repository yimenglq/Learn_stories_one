// Fill out your copyright notice in the Description page of Project Settings.


#include "TargutAummy.h"
#include "AttributeActorComponent.h"

// Sets default values
ATargutAummy::ATargutAummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AttributeComp = CreateDefaultSubobject<UAttributeActorComponent>("AttributeActorComp_Y");
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp_Y");
	RootComponent = StaticMeshComp;
	StaticMeshComp->SetCollisionObjectType(ECC_WorldDynamic);//设置碰撞对象类型 自己
	StaticMeshComp->SetGenerateOverlapEvents(true);
	
	//StaticMeshComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);//设置碰撞响应渠道  全部  失效了
	//FCollisionResponseContainer CollResContainer;
	//CollResContainer.SetResponse(ECC_WorldDynamic, ECR_Overlap);//添加 ECC_WorldDynamic  渠道  为  ECR_Overlap
	//CollResContainer.SetResponse(ECC_WorldStatic, ECR_Overlap);
	////CollResContainer.SetAllChannels(ECR_Overlap);//设置全部碰撞响应渠道 为 ECR_Overlap
	//StaticMeshComp->SetCollisionResponseToChannels(CollResContainer);//设置碰撞响应渠道
	StaticMeshComp->SetCollisionProfileName("OverlapAll");


	AttributeComp->OnBlood_volume_Changed.AddDynamic(this, &ATargutAummy::OnBldVeChanged);



}

// Called when the game starts or when spawned
void ATargutAummy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATargutAummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATargutAummy::OnBldVeChanged(AActor* Actor, UAttributeActorComponent* AttributeActorComp, float Newblood_volume, float DelVal)
{
	if (DelVal < 0.0f)
	{
		StaticMeshComp->SetScalarParameterValueOnMaterials(TEXT("TimeToHit"), GetWorld()->TimeSeconds);
	}
}

