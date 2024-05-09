// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UI/MMButtonGameWidget.h"

#include "Engine/AssetManager.h"
#include "Framework/Data/MMGameData.h"

void UMMButtonGameWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UMMButtonGameWidget::SetGameData(const FPrimaryAssetId& GameDataAssetId)
{
	if(GameDataAssetId.IsValid())
	{
		if (const UAssetManager* AssetManager = UAssetManager::GetIfInitialized())
		{
			if(const UMMGameData* GameData = Cast<UMMGameData>(AssetManager->GetPrimaryAssetObject(GameDataAssetId)))
			{
				UpdateButtonText(GameData->GameMap, GameData->GameName, GameData->GameDesc);
				if(GameData->GameImage.LoadSynchronous())
				{
					InitializeCustomButtonData();
					Texture = GameData->GameImage.LoadSynchronous();
					SetButtonSettings();
				}
			}
		}
	}
}

void UMMButtonGameWidget::UpdateButtonText(const FText& GameMapText, const FText& GameNameText,
	const FText& GameDescText)
{
	if(TextBlock)
	{
		Text = GameMapText;
		SetButtonText(GameMapText);
	}

	if(Name)
	{
		Name->SetText(GameNameText);
	}

	if(Desc)
	{
		Desc->SetText(GameDescText);
	}
}
