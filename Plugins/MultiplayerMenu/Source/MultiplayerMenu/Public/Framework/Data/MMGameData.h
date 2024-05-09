// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MMGameData.generated.h"

class UCommonActivatableWidget;
class UCommonUserWidget;
/**
 * 
 */
UCLASS()
class MULTIPLAYERMENU_API UMMGameData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Asset Settings")
	FPrimaryAssetType DataType;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(DataType, GetFName());
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=GameData, meta=(AllowedTypes="Map"))
	FPrimaryAssetId MapID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=GameData)
	TMap<FString, FString> ExtraArgs;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=GameData)
	int32 MaxPlayerCount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=GameData)
	FText GameMap;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=GameData)
	FText GameName;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=GameData)
	FText GameDesc;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=GameData)
	TSoftObjectPtr<UTexture2D> GameImage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=GameData)
	bool bShowMenu = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=GameData)
	bool bIncludeInGameList = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=UI)
	TSoftClassPtr<UCommonActivatableWidget> MainMenuClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=UI)
	TSoftClassPtr<UCommonUserWidget> GameDisplayWidgetClass;

	
};

