// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UI/MMGameSessionEntry.h"

#include "CommonGameInstance.h"
#include "CommonSessionSubsystem.h"
#include "Engine/AssetManager.h"
#include "Framework/Data/MMGameData.h"
#include "Framework/Data/StaticGameData.h"
#include "Framework/UI/MMGameSessionButton.h"

void UMMGameSessionEntry::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (SessionButton)
	{
		SessionButton->OnClicked().AddUObject(this, &UMMGameSessionEntry::OnSessionSelected);
	}
}

void UMMGameSessionEntry::OnGameDataLoaded()
{
	if (!GameDataId.IsValid())
		return;

	if (UAssetManager* AssetManager = UAssetManager::GetIfInitialized())
	{
		if (UMMGameData* GameData = Cast<UMMGameData>(AssetManager->GetPrimaryAssetObject(GameDataId)))
		{
			if (!SessionButton)
				return;

			SessionButton->SetTextDisplays(
				GameData->GameName,
				GameData->GameMap,
				FText::AsNumber(SessionSearchResult->GetPingInMs()),
				FText::AsNumber(
					SessionSearchResult->GetMaxPublicConnections() - SessionSearchResult->
					GetNumOpenPublicConnections()),
				FText::AsNumber(SessionSearchResult->GetMaxPublicConnections())

			);
		}
	}
}

void UMMGameSessionEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	SessionSearchResult = Cast<UCommonSession_SearchResult>(ListItemObject);

	if (SessionSearchResult == nullptr)
		return;

	bool bDataFound;
	FString GameDataName;
	SessionSearchResult->GetStringSetting(MM_SETTINGS_GAMEMODE, GameDataName, bDataFound);

	if (!bDataFound)
		return;
	
	const FPrimaryAssetType Type(MM_DATA_ASSET_TYPE_GAMEDATA);
	GameDataId = FPrimaryAssetId(Type, FName(*GameDataName));

	if (!GameDataId.IsValid())
		return;
	
	if (UAssetManager* AssetManager = UAssetManager::GetIfInitialized())
	{
		const TArray<FName> Bundles;
		const FStreamableDelegate DataLoadedDelegate = FStreamableDelegate::CreateUObject(
			this, &UMMGameSessionEntry::OnGameDataLoaded);

		AssetManager->LoadPrimaryAsset(GameDataId, Bundles, DataLoadedDelegate);
	}
}

void UMMGameSessionEntry::OnSessionSelected()
{
	if (!GetOwningPlayer() || !GetOwningPlayer()->GetWorld())
		return;
	
	const UCommonGameInstance* GameInstance = Cast<UCommonGameInstance>(
		GetOwningPlayer()
		->GetWorld()
		->GetGameInstance());

	if (GameInstance == nullptr)
		return;
	
	if (UCommonSessionSubsystem* SessionSubsystem = GameInstance->GetSubsystem<UCommonSessionSubsystem>())
	{
		JoinSessionHandle = SessionSubsystem->OnJoinSessionCompleteEvent.AddUObject(
			this, &UMMGameSessionEntry::OnJoinSessionComplete);
		SessionSubsystem->JoinSession(GetOwningPlayer(), SessionSearchResult);
	}
}

void UMMGameSessionEntry::OnJoinSessionComplete(const FOnlineResultInformation& Result)
{
	if (!GetOwningPlayer() || !GetOwningPlayer()->GetWorld())
	{
		return;
	}

	if (Result.bWasSuccessful)
	{
		const UCommonGameInstance* GameInstance = Cast<UCommonGameInstance>(
			GetOwningPlayer()
			->GetWorld()
			->GetGameInstance());

		if (UCommonSessionSubsystem* SessionSubsystem = GameInstance->GetSubsystem<UCommonSessionSubsystem>())
		{
			SessionSubsystem->OnJoinSessionCompleteEvent.Remove(JoinSessionHandle);
		}
	}
}
