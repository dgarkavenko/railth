// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Player/MMPlayerController.h"

#include "PrimaryGameLayout.h"
#include "Framework/Data/StaticGameData.h"
#include "Framework/Managers/MMGameState.h"

AMMPlayerController::AMMPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void AMMPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if(IsLocalController())
	{
		if(const UWorld* WorldContext = GetWorld())
		{
			if(const AMMGameState* SGameState = Cast<AMMGameState>(WorldContext->GetGameState()))
			{
				ShowMenu(SGameState->GetMenuClass());
			}			
		}
	}
}

void AMMPlayerController::ShowMenu(const TSoftClassPtr<UCommonActivatableWidget>& MenuClass)
{
	const UWorld* WorldContext = GetWorld();
	if(!WorldContext)
	{
		return;
	}

	UPrimaryGameLayout* RootLayout = UPrimaryGameLayout::GetPrimaryGameLayoutForPrimaryPlayer(WorldContext);

	if(!RootLayout)
	{
		return;
	}

	RootLayout->PushWidgetToLayerStackAsync<UCommonActivatableWidget>(
		UILayerTags::TAG_UI_LAYER_MENU,
		true,
		MenuClass,
		
		[this](EAsyncWidgetLayerState State, UCommonActivatableWidget* Screen)
		{
			switch (State)
			{
				case EAsyncWidgetLayerState::Canceled:
				case EAsyncWidgetLayerState::AfterPush:
					return;
				default: ;
			}
		});
}
