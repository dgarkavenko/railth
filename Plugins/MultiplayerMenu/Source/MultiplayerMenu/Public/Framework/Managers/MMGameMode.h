// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MMGameMode.generated.h"

class AMMPlayerController;
class UMMGameData;
/**
 * 
 */
UCLASS()
class MULTIPLAYERMENU_API AMMGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMMGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void InitGameState() override;
	virtual void GenericPlayerInitialization(AController* C) override;
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	virtual bool PlayerCanRestart_Implementation(APlayerController* Player) override;
	virtual void FailedToRestartPlayer(AController* NewPlayer) override;

	void RequestPlayerRestartNextFrame(AController* Controller, bool bForceReset = false);
	
protected:

	void HandleGameDataAssignment();
	void OnGameDataAssignment();
	void OnGameDataLoaded();
	bool IsGameDataLoaded() const { return CurrentGameDataAssetId.IsValid(); }
	UMMGameData* GetGameData() const;
	
	UFUNCTION()
	void OnGameReady();

	void InitializePlayers();

	UPROPERTY()
	bool bGameReady = false;

	UPROPERTY()
	FPrimaryAssetId CurrentGameDataAssetId;

	UPROPERTY()
	TArray<AMMPlayerController*> SessionPlayers;
};
