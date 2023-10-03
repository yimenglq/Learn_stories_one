// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargutAummy.generated.h"

UCLASS()
class LEARN_STORIES_ONE_API ATargutAummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargutAummy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
	class UAttributeActorComponent* AttributeComp;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComp;


public:
	UFUNCTION()
	void OnBldVeChanged(AActor* Actor, UAttributeActorComponent* AttributeActorComp, float Newblood_volume, float DelVal);


};
