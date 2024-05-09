// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UI/MMGameUIManager.h"

#include "CommonLocalPlayer.h"
#include "GameUIPolicy.h"
#include "PrimaryGameLayout.h"
#include "GameFramework/HUD.h"

UMMGameUIManagerSubsystem::UMMGameUIManagerSubsystem()
{
	// verify(DefaultUIPolicyClass != nullptr);
}

void UMMGameUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	TickHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UMMGameUIManagerSubsystem::Tick), 0.0f);
}

void UMMGameUIManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
	FTSTicker::GetCoreTicker().RemoveTicker(TickHandle);
}

bool UMMGameUIManagerSubsystem::Tick(float DeltaTime)
{
	SyncRootLayoutVisibilityToShowHUD();
	return true;
}

void UMMGameUIManagerSubsystem::SyncRootLayoutVisibilityToShowHUD()
{
	UGameUIPolicy* Policy = GetCurrentUIPolicy();
	
	if(Policy == nullptr)
		return;

	for(const ULocalPlayer* LocalPlayer : GetGameInstance()->GetLocalPlayers())
	{
		bool bShouldShow = true;
		if (const APlayerController* PC = LocalPlayer->GetPlayerController(GetWorld()))
		{
			const AHUD* HUD = PC->GetHUD();
			if(HUD && !HUD->bShowHUD)
			{
				bShouldShow = false;
			}
		}

		if (UPrimaryGameLayout* RootLayout = Policy->GetRootLayout(CastChecked<UCommonLocalPlayer>(LocalPlayer)))
		{
			const ESlateVisibility DesiredVisibility = bShouldShow ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed;
			RootLayout->SetVisibility(DesiredVisibility);			
		}
	}
}
