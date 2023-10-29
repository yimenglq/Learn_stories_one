// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include"EnvironmentQuery\EnvQueryTypes.h"
#include "YGameModeBase.generated.h"

/**
 * 
 */

UCLASS()
class LEARN_STORIES_ONE_API AYGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	


protected:

	UPROPERTY(EditAnywhere,Category = "DIY|GameMode")
	float	c_TimeRate;//定时器时间

	UPROPERTY(EditAnywhere , Category = "DIY|GameMode")
	class	UEnvQuery* c_QueryTemp;//eqs查询模板

	UPROPERTY(EditAnywhere, Category = "DIY|GameMode")
	TSubclassOf<AActor>	c_AI_NPC;//生成的ai小兵

	int c_ActorNum;

	FTimerHandle c_TimerHandle;

	UPROPERTY(EditAnywhere, Category = "DIY|GameMode")
	UCurveFloat* c_CurveFloat;

	UPROPERTY(EditAnywhere, Category = "DIY|GameMode|Rebirth")
	float	c_ActorRebirthTime;

	TMap<APlayerController*, UUserWidget* >  c_ControllerAttWidgetMap;


protected:

	void SpawnInit();

	UFUNCTION()
	void	OnQueryFinished(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);
	UFUNCTION()
	void OnDestroyedSpawnFun(AActor* DestroyedActor);
public:
	AYGameModeBase();
	virtual void StartPlay()override;

	virtual void PostInitializeComponents()override;

	virtual void RebirthRules(APlayerController* RebirthActorPlayerController);//重生规则

	void	AddControllerAttWidget(APlayerController* InPlayerControllerKey, UUserWidget* InWidgetVal);

	UFUNCTION(BlueprintCallable, Category = "DIY|GameMode")
	UUserWidget* IsControllerAttWidget(APlayerController* InPlayerControllerKey);

};
