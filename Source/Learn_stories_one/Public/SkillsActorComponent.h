// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillsActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEARN_STORIES_ONE_API USkillsActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillsActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;




public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
protected:
	
	UPROPERTY(EditAnywhere, Category = "DIY|Skills")
	TSubclassOf<AActor>	Skill_1;//技能一
	UPROPERTY(EditAnywhere, Category = "DIY|Skills")
	TSubclassOf<AActor>	Skill_2;//技能一
	UPROPERTY(EditAnywhere, Category = "DIY|Skills")
	TSubclassOf<AActor>	Skill_3;//技能一
	UPROPERTY(EditAnywhere, Category = "DIY|Skills")
	TSubclassOf<AActor>	Skill_4;//技能一
	
	UPROPERTY(EditAnywhere, Category = "DIY|Skills|end")
	float end;//攻击准确最远距离
	


	//FTransform Transform;
	
	FRotator PlayerControllerRotator;
	FVector OwnerCameraCompLocation;

	


public:
	UPROPERTY(EditAnywhere,Category = "DIY|Draw")
	TSubclassOf<AActor> ADrawShpere;
	AActor* A_this_spawnShpere;
	UPROPERTY(EditAnywhere, Category = "DIY|Teleportation")
	TSubclassOf<AActor> ATeleportation;
	AActor* A_this_ATeleportation;

	void BlackHole_Spawn();

	void DrawShpere();

	void Teleportation();

	FVector GetCrosshairend();//屏幕中心 瞄准最远点

};
