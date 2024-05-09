// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonTabListWidgetBase.h"
#include "CommonUserTypes.h"
#include "Blueprint/IUserObjectListEntry.h"

#include "MMGameSessionEntry.generated.h"

class UCommonSession_SearchResult;
class UMMGameSessionButton;

/**
 * 
 */
UCLASS()
class MULTIPLAYERMENU_API UMMGameSessionEntry : public UCommonTabListWidgetBase, public IUserObjectListEntry
{
	GENERATED_BODY()

public:

	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void OnGameDataLoaded();
	
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

protected:

	UFUNCTION()
	void OnSessionSelected();

	UFUNCTION()
	void OnJoinSessionComplete(const FOnlineResultInformation& Result);

	UPROPERTY()
	UCommonSession_SearchResult* SessionSearchResult;
	
	UPROPERTY(BlueprintReadOnly, meta= (BindWidget))
	UMMGameSessionButton* SessionButton;

	FDelegateHandle JoinSessionHandle;

	UPROPERTY()
	FPrimaryAssetId GameDataId;
};
