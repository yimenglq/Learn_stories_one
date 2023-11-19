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



	//设置关键帧  曲线
	FRichCurveKey CurveKey;
	CurveKey.Time = 0;
	CurveKey.Value = 0;
	CurveFloat->FloatCurve.Keys.Add(CurveKey);
	CurveKey.Time = 2;
	CurveKey.Value = 1;
	CurveFloat->FloatCurve.Keys.Add(CurveKey);
	//end
	//设置时间轴长短
	TimeLineComp->SetTimelineLength(2.0f);
	//设置时间轴控件调用函数
	FOnTimelineFloat OnTimelineFloat;
	OnTimelineFloat.BindDynamic(this, &ATreasureChestsActor::timeLinefunion);
	//OnTimelineFloat.BindUFunction(this, "timeLinefunion");//这个也可以
	TimeLineComp->AddInterpFloat(CurveFloat, OnTimelineFloat);//把曲线和调用函数加载入时间轴
	

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

void ATreasureChestsActor::timeLinefunion(float Output)//时间轴调用函数
{
	

		//FMath::Lerp线性插值 根据第3个参数 线性计算前两个参数
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
	//	TimeLineComp->Play();//播放时间轴
	//	bOpen = 1;
	//}
	//else
	//{
	//	TimeLineComp->Reverse();//反向播放
	//	bOpen = 0;
	//}

	bLidOpened ? LidRoll = 90 : LidRoll = 0;
	StaticMeshCompLid->SetRelativeRotation(FRotator(0,0, LidRoll) );


}
