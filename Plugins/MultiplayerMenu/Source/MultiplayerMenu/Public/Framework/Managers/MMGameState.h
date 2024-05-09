// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MMGameState.generated.h"

class UMMGameData;
class UCommonActivatableWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStateReadyDelegate);

/**
 * 
 */
UCLASS()
class MULTIPLAYERMENU_API AMMGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	AMMGameState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	void SetGameData(UMMGameData* NewGameData);
	bool ShouldShowMenu() const;
	TSoftClassPtr<UCommonActivatableWidget>& GetMenuClass() const;

	FOnGameStateReadyDelegate OnGameStateReady;

protected:

	UPROPERTY(ReplicatedUsing=OnRep_GameData)
	UMMGameData* GameData;

	UFUNCTION()
	void OnRep_GameData();

};