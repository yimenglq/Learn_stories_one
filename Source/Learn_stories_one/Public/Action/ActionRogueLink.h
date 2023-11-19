#pragma once
#include "CoreMinimal.h"


static void LogOnScreen(UObject* WorldContext, FString Msg, FColor Color = FColor::White, float Duration = 5.0f)
{
	if (!ensure(WorldContext))
	{
		return;
	}

	UWorld* world = WorldContext->GetWorld();
	if (!ensure(world))
	{
		return;
	}
	FString NetPreFix = world->IsNetMode(NM_Client) ? "[CLIENT]" : "[SERVER]";
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Duration, Color, NetPreFix + Msg);
	}


}

