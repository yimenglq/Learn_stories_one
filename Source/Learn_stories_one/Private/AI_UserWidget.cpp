// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_UserWidget.h"
#include <Kismet/GameplayStatics.h>
#include <Blueprint/WidgetLayoutLibrary.h>
#include"Components\SizeBox.h"
#include"Components\Image.h"
#include <AttributeActorComponent.h>

UAI_UserWidget::UAI_UserWidget(const FObjectInitializer& ObjectInitializer):UUserWidget(ObjectInitializer)
{
	c_OldBlood = c_NewBlood = 0;
	c_WorldOffetValue = { 0,0,0 };
	//c_bOldBloodInit = false;

	
}

void UAI_UserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry,InDeltaTime);
	FVector2D UI2dPos;
	if(c_AttachedActor != nullptr)
	if (UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), c_AttachedActor->GetActorLocation()+c_WorldOffetValue, UI2dPos)) //3D世界坐标转换为2D屏幕坐标
	{
		float ViewScale = UWidgetLayoutLibrary::GetViewportScale(c_AttachedActor);//获取视口缩放  

		UI2dPos /= ViewScale;
		c_SizeBoxBlood->SetRenderTranslation(UI2dPos);

		UAttributeActorComponent * attComp = UAttributeActorComponent::GetAttributeActorComponent(c_AttachedActor);
		if (attComp)
		{
			
		
			c_NewBlood = attComp->GetBlood_volume();
			c_ScalarParameterValue.ParameterName = c_ParameterName;
			c_ScalarParameterValue.Value = c_NewBlood / c_OldBlood;
		}

		GetOwningPlayerPawn();
		c_Bloodimg->GetDynamicMaterial()->SetScalarParameterValue(c_ScalarParameterValue.ParameterName, c_ScalarParameterValue.Value);
	}
	//UWidgetLayoutLibrary::GetViewportWidgetGeometry(GetWorld());


}

//FReply UAI_UserWidget::NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
//{
//	return FReply();
//}
