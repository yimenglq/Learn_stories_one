// Fill out your copyright notice in the Description page of Project Settings.


#include "TreasureChestsActor.h"
#include"Components\TimelineComponent.h"
#include"Curves\CurveFloat.h"
#include <Net/UnrealNetwork.h>


// Sets default values
ATreasureChestsActor::ATreasureChestsActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshCompBase = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshCompBase_Y");
	StaticMeshCompLid = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshCompLid_Y");
	TimeLineComp = CreateDefaultSubobject<UTimelineComponent>("TimeLineComp_Y");
	CurveFloat = CreateDefaultSubobject<UCurveFloat>("CurveFloat_Y");

	RootComponent = StaticMeshCompBase;
	StaticMeshCompLid->SetupAttachment(StaticMeshCompBase);

	StaticMeshCompBase->SetSimulatePhysics(true);
	
	LidPitch = LidYaw = LidRoll = 0;



	//���ùؼ�֡  ����
	FRichCurveKey CurveKey;
	CurveKey.Time = 0;
	CurveKey.Value = 0;
	CurveFloat->FloatCurve.Keys.Add(CurveKey);
	CurveKey.Time = 2;
	CurveKey.Value = 1;
	CurveFloat->FloatCurve.Keys.Add(CurveKey);
	//end
	//����ʱ���᳤��
	TimeLineComp->SetTimelineLength(2.0f);
	//����ʱ����ؼ����ú���
	FOnTimelineFloat OnTimelineFloat;
	OnTimelineFloat.BindDynamic(this, &ATreasureChestsActor::timeLinefunion);
	//OnTimelineFloat.BindUFunction(this, "timeLinefunion");//���Ҳ����
	TimeLineComp->AddInterpFloat(CurveFloat, OnTimelineFloat);//�����ߺ͵��ú���������ʱ����
	

	SetReplicates(true);
}

// Called when the game starts or when spawned
void ATreasureChestsActor::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ATreasureChestsActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ATreasureChestsActor::Interactive_Implementation(APawn* InOwPawn)
{

	
	bLidOpened = !bLidOpened;
	OnRep_LidOpened();
}

void ATreasureChestsActor::timeLinefunion(float Output)//ʱ������ú���
{
	

		//FMath::Lerp���Բ�ֵ ���ݵ�3������ ���Լ���ǰ��������
	StaticMeshCompLid->SetRelativeRotation(FMath::Lerp(FRotator(0, 0, 0), FRotator(LidPitch, LidYaw, LidRoll), Output));
}

void ATreasureChestsActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATreasureChestsActor, bLidOpened);
	//DOREPLIFETIME(ATreasureChestsActor, TimeLineComp);

}
void ATreasureChestsActor::OnRep_LidOpened()
{
	//static bool bOpen = 0;
	//if (!bOpen)
	//{
	//	TimeLineComp->Play();//����ʱ����
	//	bOpen = 1;
	//}
	//else
	//{
	//	TimeLineComp->Reverse();//���򲥷�
	//	bOpen = 0;
	//}

	bLidOpened ? LidRoll = 90 : LidRoll = 0;
	StaticMeshCompLid->SetRelativeRotation(FRotator(0,0, LidRoll) );


}
