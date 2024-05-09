// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UI/MMGameDisplayListWidget.h"

#include "Components/PanelWidget.h"
#include "Engine/AssetManager.h"
#include "Framework/Data/MMGameData.h"
#include "Framework/Data/StaticGameData.h"
#include "Framework/UI/MMGameDisplayWidget.h"

void UMMGameDisplayListWidget::NativeConstruct()
{
	Super::NativeConstruct();
	LoadGameList();
}

void UMMGameDisplayListWidget::LoadGameList()
{
	if(GameList)
	{
		GameList->ClearChildren();

		if(UAssetManager* AssetManager = UAssetManager::GetIfInitialized())
		{
			TArray<FPrimaryAssetId> GameDataAssets;
			const FPrimaryAssetType GroupAssetType(MM_DATA_ASSET_TYPE_GAMEDATA);
			AssetManager->GetPrimaryAssetIdList(GroupAssetType, GameDataAssets);

			if(GameDataAssets.Num() < 1)
			{
				UE_LOG(LogTemp, Error, TEXT("UMMGameDisplayListWidget Failed to get GameDatAssets"));
				return;
			}

			const TArray<FName> Bundles;
			const FStreamableDelegate GroupDataLoadedDelegate =
				FStreamableDelegate::CreateUObject (
					this,
					&UMMGameDisplayListWidget::OnGameDataLoaded,
					GameDataAssets);
			
			AssetManager->LoadPrimaryAssets(GameDataAssets, Bundles, GroupDataLoadedDelegate);
		}
	}
}

void UMMGameDisplayListWidget::OnGameDataLoaded(TArray<FPrimaryAssetId> AssetsIds)
{
	if(!GetOwningPlayer() || !GetOwningPlayer()->GetWorld())
	{
		return;
	}

	const UAssetManager* AssetManager = UAssetManager::GetIfInitialized();

	if(AssetManager == nullptr)
		return;
		
	for (int i = 0; i < AssetsIds.Num(); ++i)
	{
		if(const UMMGameData* GameData = Cast<UMMGameData>(AssetManager->GetPrimaryAssetObject(AssetsIds[i])))
		{
			if(!GameData->bIncludeInGameList || !GameData->GameDisplayWidgetClass.IsValid())
				continue;

			UMMGameDisplayWidget* GameDisplayWidget =
				CreateWidget<UMMGameDisplayWidget>(
					GetOwningPlayer()->GetWorld(),
					GameData->GameDisplayWidgetClass.LoadSynchronous());

			GameDisplayWidget->SetGameData(AssetsIds[i]);
			GameList->AddChild(GameDisplayWidget);			
		}
	}

	OnGameListCreation();

}

TArray<UWidget*> UMMGameDisplayListWidget::GetWidgetList()
{
	if(GameList)
	{
		return GameList->GetAllChildren();
	}

	return TArray<UWidget*>();
}

void UMMGameDisplayListWidget::OnGameListCreation()
{
	OnGameListCreated.Broadcast();
	TArray<UWidget*> DisplayWidgets = GetWidgetList();
	for (int i = 0; i < DisplayWidgets.Num(); ++i)
	{
		if(UMMGameDisplayWidget* DisplayWidget = Cast<UMMGameDisplayWidget>(DisplayWidgets[i]))
		{
			DisplayWidget->OnGameDisplaySelected.AddDynamic(this, &UMMGameDisplayListWidget::OnGameDisplaySelection);
		}
	}
}

void UMMGameDisplayListWidget::OnGameDisplaySelection(const FPrimaryAssetId& SelectedGameData)
{
	OnGameSelected.Broadcast(SelectedGameData);
}
