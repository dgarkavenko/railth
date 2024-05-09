// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "MMGameDisplayWidget.generated.h"


class UMMButtonGameWidget;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameSelectedDisplayDelegate, const FPrimaryAssetId&, SelectedGameData);

UCLASS(Abstract)
class MULTIPLAYERMENU_API UMMGameDisplayWidget : public UCommonUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;
	void SetGameData(const FPrimaryAssetId& Data);
	FPrimaryAssetId& GetGameDataAssetId();

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UMMButtonGameWidget* GameButtonWidget;
	
	FOnGameSelectedDisplayDelegate OnGameDisplaySelected;

protected:
	
	UPROPERTY()
	FPrimaryAssetId GameDataId;

	UFUNCTION()
	void OnGameSelection();
};
