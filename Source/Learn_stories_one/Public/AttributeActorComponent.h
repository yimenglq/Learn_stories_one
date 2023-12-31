// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeActorComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnBlood_volume_Changed, AActor*, Actor, UAttributeActorComponent*, AttributeActorComp, float, Newblood_volume ,float, DelVal);

/*
	属性组件类
*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEARN_STORIES_ONE_API UAttributeActorComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this component's properties
	UAttributeActorComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere,Replicated, Category = "DIY|Attribute")//暴露给蓝图  和给编辑器修改
		int blood_volume;//当前血量
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Replicated, Category = "DIY|Attribute")
		int Maxblood;//最大血量

protected:
	//RPC
	UFUNCTION(NetMulticast,Unreliable)
	void MulticastBoloodChanged(AActor* InstigatorActor, float NewBlood , float Delta );

	UFUNCTION(Server,Reliable)
	void ServerBloodChanged(AActor* InstigatorActor, float NewBlood, float Delta);

public:
	UFUNCTION(BlueprintCallable,Category = "DIY|Attribute", meta = (GetAttributeActorComp))
	static UAttributeActorComponent* GetAttributeActorComponent(AActor* InActor);


public:
	UPROPERTY(BlueprintAssignable,Category = "DIY|Attribute|Event")//只能与组播委托共用。公开属性在蓝图中指定。
	FOnBlood_volume_Changed OnBlood_volume_Changed;
	UFUNCTION(BlueprintCallable, Category = "DIY|Attribute")
	void	ReviseBlood_volume(int InVal);

	UFUNCTION(BlueprintCallable, Category = "DIY|Attribute")//给蓝图使用 函数
	int GetBlood_volume();
	void	GetBlood_volume(int& OutVal);
	void SetBloodVolume(int InBloodVal);

	
	UFUNCTION(BlueprintCallable, Category = "DIY|Attribute")
	bool IsAlive();//是否存活 当前血量是否大于零







};



