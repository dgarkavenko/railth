// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UI/MMMenuMultiplayerWidget.h"
#include "Framework/UI/MMHostSessionWidget.h"
#include "Framework/UI/MMJoinSessionWidget.h"

#include "PrimaryGameLayout.h"
#include "Framework/Data/StaticGameData.h"
#include "Framework/UI/MMButtonBase.h"
#include "Kismet/KismetSystemLibrary.h"


void UMMMenuMultiplayerWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	HostButton->OnClicked().AddUObject(this, &UMMMenuMultiplayerWidget::OnHostButtonClicked);
	JoinButton->OnClicked().AddUObject(this, &UMMMenuMultiplayerWidget::OnJoinButtonClicked);
	ExitButton->OnClicked().AddUObject(this, &UMMMenuMultiplayerWidget::OnExitButtonClicked);
}

UWidget* UMMMenuMultiplayerWidget::NativeGetDesiredFocusTarget() const
{
	if (HostButton)
	{
		return HostButton;
	}

	return Super::NativeGetDesiredFocusTarget();
}

void UMMMenuMultiplayerWidget::AddWidgetToRootLayout(TSoftClassPtr<UCommonActivatableWidget> WidgetClass)
{
	if (const UWorld* WorldContext = GetWorld())
	{
		if (UPrimaryGameLayout* Root = UPrimaryGameLayout::GetPrimaryGameLayoutForPrimaryPlayer(WorldContext))
		{
			Root->PushWidgetToLayerStackAsync<UCommonActivatableWidget>(
				UILayerTags::TAG_UI_LAYER_MENU,
				true,
				WidgetClass,
				[this](EAsyncWidgetLayerState State,
				       UCommonActivatableWidget* Screen)
				{
					switch (State)
					{
						case EAsyncWidgetLayerState::Canceled:
						case EAsyncWidgetLayerState::AfterPush:
							return;
						default: ;
					}
				}
			);
		}
	}
}

void UMMMenuMultiplayerWidget::OnHostButtonClicked()
{
	if (!HostWidgetClass.IsNull())
	{
		AddWidgetToRootLayout(HostWidgetClass);
	}
}

void UMMMenuMultiplayerWidget::OnJoinButtonClicked()
{
	if (!JoinWidgetClass.IsNull())
	{
		AddWidgetToRootLayout(JoinWidgetClass);
	}
}

void UMMMenuMultiplayerWidget::OnExitButtonClicked()
{
	if (GetOwningPlayer() == nullptr)
		return;

	if (GetWorld() == nullptr)
		return;

	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
}
