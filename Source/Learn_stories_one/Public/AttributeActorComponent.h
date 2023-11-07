// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeActorComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnBlood_volume_Changed, AActor*, Actor, UAttributeActorComponent*, AttributeActorComp, float, Newblood_volume ,float, DelVal);


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
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DIY|Attribute")//��¶����ͼ  �͸��༭���޸�
		int blood_volume;
	UPROPERTY(BlueprintReadOnly, EditAnywhere , Category = "DIY|Attribute")
		int Maxblood;//���Ѫ��
public:
	UFUNCTION(BlueprintCallable,Category = "DIY|Attribute", meta = (GetAttributeActorComp))
	static UAttributeActorComponent* GetAttributeActorComponent(AActor* InActor);


public:
	UPROPERTY(BlueprintAssignable,Category = "DIY|Attribute|Event")//ֻ�����鲥ί�й��á�������������ͼ��ָ����
	FOnBlood_volume_Changed OnBlood_volume_Changed;
	UFUNCTION(BlueprintCallable, Category = "DIY|Attribute")
	void	ReviseBlood_volume(int InVal);

	UFUNCTION(BlueprintCallable, Category = "DIY|Attribute")//����ͼʹ�� ����
	int GetBlood_volume();
	void	GetBlood_volume(int& OutVal);
	
	UFUNCTION(BlueprintCallable, Category = "DIY|Attribute")
	bool IsAlive();





};



