// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "MMGameDisplayListWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameListCreatedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameSelectedDelegate, const FPrimaryAssetId&, SelectedGameData);

UCLASS(Abstract)
class MULTIPLAYERMENU_API UMMGameDisplayListWidget : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	FOnGameListCreatedDelegate OnGameListCreated;
	FOnGameSelectedDelegate OnGameSelected;
	TArray<UWidget*> GetWidgetList();

protected:
	void LoadGameList();
	void OnGameDataLoaded(TArray<FPrimaryAssetId> AssetsIds);
	void OnGameListCreation();

	UFUNCTION()
	void OnGameDisplaySelection(const FPrimaryAssetId& SelectedGameData);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UPanelWidget* GameList;
};


