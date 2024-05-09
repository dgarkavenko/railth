// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework/UI/MMGameDisplayWidget.h"
#include "Framework/UI/MMButtonGameWidget.h"

void UMMGameDisplayWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if(GameButtonWidget)
	{
		GameButtonWidget->OnClicked().AddUObject(this, &UMMGameDisplayWidget::OnGameSelection);
	}
}

void UMMGameDisplayWidget::SetGameData(const FPrimaryAssetId& Data)
{
	if(Data.IsValid() && GameButtonWidget)
	{
		GameDataId = Data;
		GameButtonWidget->SetGameData(Data);
	}
}

FPrimaryAssetId& UMMGameDisplayWidget::GetGameDataAssetId()
{
	return GameDataId;
}

void UMMGameDisplayWidget::OnGameSelection()
{
	OnGameDisplaySelected.Broadcast(GameDataId);
}
