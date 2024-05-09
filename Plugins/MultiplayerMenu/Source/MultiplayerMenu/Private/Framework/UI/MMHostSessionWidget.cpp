// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UI/MMHostSessionWidget.h"

#include "CommonGameInstance.h"
#include "CommonSessionSubsystem.h"
#include "CommonUserSubsystem.h"
#include "MMUtils.h"
#include "PrimaryGameLayout.h"
#include "Framework/Data/MMGameData.h"
#include "Framework/Data/StaticGameData.h"
#include "Framework/UI/MMButtonBase.h"
#include "Framework/UI/MMGameDisplayListWidget.h"
#include "Framework/UI/MMGameDisplayWidget.h"

void UMMHostSessionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	NetMode = ECommonSessionOnlineMode::Online;
	InitTextDisplays();

	if(NetModeButton)
	{
		NetModeButton->OnClicked().AddUObject(this, &UMMHostSessionWidget::OnNetModeClicked);
	}

	if(ChangeSettingsButton)
	{
		ChangeSettingsButton->OnClicked().AddUObject(this, &UMMHostSessionWidget::OnSettingsButtonClicked);
	}

	if(LaunchButton)
	{
		LaunchButton->OnClicked().AddUObject(this, &UMMHostSessionWidget::OnLaunchButtonClicked);
	}
	
	if(BackButton)
	{
		BackButton->OnClicked().AddUObject(this, &UMMHostSessionWidget::OnBackButtonClicked);
	}

	if(GameList)
	{
		GameList->OnGameListCreated.AddDynamic(this, &UMMHostSessionWidget::OnGameListCreated);
		GameList->OnGameSelected.AddDynamic(this, &UMMHostSessionWidget::OnGameSelected);
	}

	if(NetModeText)
		NetModeText->SetText(UEnum::GetDisplayValueAsText(NetMode));

	if(GameSettingsText)
		GameSettingsText->SetText(UEnum::GetDisplayValueAsText(HostSettings));
}

void UMMHostSessionWidget::OnNetModeClicked()
{
	MMUtils::IncrementEnum(NetMode, ECommonSessionOnlineMode::Online);
	
	if(NetModeText)
		NetModeText->SetText(UEnum::GetDisplayValueAsText(NetMode));
}

void UMMHostSessionWidget::OnSettingsButtonClicked()
{
	MMUtils::IncrementEnum(HostSettings, EHostSettings::C);
	if(GameSettingsText)
		GameSettingsText->SetText(UEnum::GetDisplayValueAsText(HostSettings));
}

void UMMHostSessionWidget::OnUserLogin(const UCommonUserInfo* UserInfo, bool bSuccess, FText Error,
	ECommonUserPrivilege RequestedPrivilege, ECommonUserOnlineContext OnlineContext)
{
	if(!bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: login failed"), TEXT(__FUNCTION__));
		return;
	}

	HostSession();
}

void UMMHostSessionWidget::OnSessionCreated(const FOnlineResultInformation& OnlineResultInformation)
{		
	if(!OnlineResultInformation.bWasSuccessful)
		UE_LOG(LogTemp, Error, TEXT("%s: session creation failed"), TEXT(__FUNCTION__));
}

UCommonSession_HostSessionRequest* UMMHostSessionWidget::CreateHostSessionRequest()
{
	UCommonSession_HostSessionRequest* Request = NewObject<UCommonSession_HostSessionRequest>();

	if(!GameDataId.IsValid())
		return Request;
	
	const UAssetManager* AssetManager = UAssetManager::GetIfInitialized();

	if(!AssetManager)
		return Request;
	
	if(const UMMGameData* GameData = Cast<UMMGameData>(AssetManager->GetPrimaryAssetObject(GameDataId)))
	{
		const FString GameDataName = GameDataId.PrimaryAssetName.ToString();
		Request->ModeNameForAdvertisement = GameDataName;
		Request->OnlineMode = ECommonSessionOnlineMode::Online;
		Request->bUseLobbies = true;
		Request->MapID = GameData->MapID;
		Request->ExtraArgs = GameData->ExtraArgs;
		Request->ExtraArgs.Add(MM_SETTINGS_GAMEMODE, GameDataName);
		Request->MaxPlayerCount = GameData->MaxPlayerCount;
	}
	
	return Request;
}

void UMMHostSessionWidget::HostSession()
{
	if(!GetOwningPlayer() || !GetOwningPlayer()->GetWorld())
	{
		return;
	}

	if(const UCommonGameInstance* GameInstance = Cast<UCommonGameInstance>(GetOwningPlayer()->GetWorld()->GetGameInstance()))
	{
		if (auto* SessionSubsystem = GameInstance->GetSubsystem<UCommonSessionSubsystem>())
		{
			SessionSubsystem->OnCreateSessionCompleteEvent.AddUObject(this, &UMMHostSessionWidget::OnSessionCreated);
			UCommonSession_HostSessionRequest* Request = CreateHostSessionRequest();
			SessionSubsystem->HostSession(GetOwningPlayer(), Request);
		}
	}
}

void UMMHostSessionWidget::OnLaunchButtonClicked()
{
	if(!GetOwningPlayer() || !GetOwningPlayer()->GetWorld())
	{
		return;
	}	

	if(const UCommonGameInstance* GameInstance = Cast<UCommonGameInstance>(GetOwningPlayer()->GetWorld()->GetGameInstance()))
	{
		if (auto* UserSubsystem = GameInstance->GetSubsystem<UCommonUserSubsystem>())
		{
			UserSubsystem->OnUserInitializeComplete.AddDynamic(this, &UMMHostSessionWidget::OnUserLogin);
			UserSubsystem->TryToLoginForOnlinePlay(0);
		}
	}
}

void UMMHostSessionWidget::OnBackButtonClicked()
{
	if(UPrimaryGameLayout* RootLayout = UPrimaryGameLayout::GetPrimaryGameLayoutForPrimaryPlayer(GetWorld()))
	{
		RootLayout->FindAndRemoveWidgetFromLayer(this);
	}
}

void UMMHostSessionWidget::OnGameListCreated()
{
	TArray<UWidget*> DisplayWidgets = GameList->GetWidgetList();

	if(!DisplayWidgets.IsValidIndex(0))
		return;

	if(UMMGameDisplayWidget* DisplayWidget = Cast<UMMGameDisplayWidget>(DisplayWidgets[0]))
	{
		const FPrimaryAssetId& DisplayGameDataId = DisplayWidget->GetGameDataAssetId();
		OnGameSelected(DisplayGameDataId);
	}
}

void UMMHostSessionWidget::OnGameSelected(const FPrimaryAssetId& SelectedGameDataId)
{
	if(!SelectedGameDataId.IsValid())
		return;

	GameDataId = SelectedGameDataId;

	const UAssetManager* AssetManager = UAssetManager::GetIfInitialized();

	if(!AssetManager)
		return;

	if(const UMMGameData* GameData = Cast<UMMGameData>(AssetManager->GetPrimaryAssetObject(SelectedGameDataId)))
	{
		if(SelectedGameTitleText)
			SelectedGameTitleText->SetText(GameData->GameName);
	}
}


void UMMHostSessionWidget::InitTextDisplays() const
{
	
}
