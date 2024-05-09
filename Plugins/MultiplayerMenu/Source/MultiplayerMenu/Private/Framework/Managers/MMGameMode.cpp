// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\..\Public\Framework\Managers\MMGameMode.h"

#include "Engine/AssetManager.h"
#include "..\..\..\Public\Framework\Data\MMGameData.h"
#include "Framework/Data/StaticGameData.h"
#include "..\..\..\Public\Framework\Managers\MMGameState.h"
#include "..\..\..\Public\Framework\Player\MMPlayerController.h"
#include "Kismet/GameplayStatics.h"

AMMGameMode::AMMGameMode(const FObjectInitializer& ObjectInitializer)  : Super(ObjectInitializer)
{
	bGameReady = false;
}

void AMMGameMode::InitGameState()
{
	Super::InitGameState();
	SessionPlayers.Empty();

	if(AMMGameState* MMGameState = Cast<AMMGameState>(GameState))
	{
		MMGameState->OnGameStateReady.AddDynamic(this, &AMMGameMode::OnGameReady);
	}

	GetWorldTimerManager().SetTimerForNextTick(this, &ThisClass::HandleGameDataAssignment);
}

void AMMGameMode::GenericPlayerInitialization(AController* C)
{
	Super::GenericPlayerInitialization(C);
	AMMPlayerController* Player = Cast<AMMPlayerController>(C);
	check(Player);
	SessionPlayers.AddUnique(Player);
}

void AMMGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	if(IsGameDataLoaded())
	{
		Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	}		
}

bool AMMGameMode::PlayerCanRestart_Implementation(APlayerController* Player)
{
	return bGameReady && Super::PlayerCanRestart_Implementation(Player);
}

void AMMGameMode::FailedToRestartPlayer(AController* NewPlayer)
{
	if(!bGameReady)
	{
		RequestPlayerRestartNextFrame(NewPlayer);
		return;
	}	
	
	if(APlayerController* NewPlayerController = Cast<APlayerController>(NewPlayer))
	{
		if(!PlayerCanRestart(NewPlayerController))
		{
			UE_LOG(LogTemp, Log, TEXT("FailedToRestartPlayer(%s)"), *GetPathNameSafe(NewPlayer))
			return;
		}		
		
		RequestPlayerRestartNextFrame(NewPlayer);
	}
}

void AMMGameMode::RequestPlayerRestartNextFrame(AController* Controller, bool bForceReset)
{
	if(bForceReset)
		Controller->Reset();

	if(APlayerController* PC = Cast<APlayerController>(Controller))
	{
		GetWorldTimerManager().SetTimerForNextTick(PC, &APlayerController::ServerRestartPlayer_Implementation);
	}
}

void AMMGameMode::HandleGameDataAssignment()
{
	if(!CurrentGameDataAssetId.IsValid() &&
		UGameplayStatics::HasOption(OptionsString, MM_SETTINGS_GAMEMODE))
	{
		const FString GameDataFromOptions =
			UGameplayStatics::ParseOption(OptionsString, MM_SETTINGS_GAMEMODE);
		
		CurrentGameDataAssetId =
			FPrimaryAssetId(FPrimaryAssetType(UMMGameData::StaticClass()->GetFName()), FName(*GameDataFromOptions));
	}
	
	if(!CurrentGameDataAssetId.IsValid())
	{
		CurrentGameDataAssetId = FPrimaryAssetId(FPrimaryAssetType(MM_DATA_ASSET_TYPE_GAMEDATA), MM_DATA_ASSET_TYPE_GAMEDATA_DEFAULT);
	}
	
	if(CurrentGameDataAssetId.IsValid())
	{
		OnGameDataAssignment();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AMMGameMode::HandleGameDataAssignment()"));
	}
}

void AMMGameMode::OnGameDataAssignment()
{
	UAssetManager* AssetManager = UAssetManager::GetIfInitialized();
	verify(AssetManager);
	
	if(!CurrentGameDataAssetId.IsValid())
		return;
	
	TArray<FName> Bundles;
	Bundles.Add(MM_DATA_ASSET_BUNDLE_GAME);
	const FStreamableDelegate GroupDataLoadedDelegate = FStreamableDelegate::CreateUObject(this, &AMMGameMode::OnGameDataLoaded);
	AssetManager->LoadPrimaryAsset(CurrentGameDataAssetId, Bundles, GroupDataLoadedDelegate);

}

void AMMGameMode::OnGameDataLoaded()
{
	if(!CurrentGameDataAssetId.IsValid())
		return;

	AMMGameState* MMGameState = Cast<AMMGameState>(GameState);
	UMMGameData* GameData = GetGameData();

	if(MMGameState != nullptr && GameData != nullptr)
	{
		MMGameState->SetGameData(GameData);	
	}		
}

UMMGameData* AMMGameMode::GetGameData() const
{
	if(!CurrentGameDataAssetId.IsValid())
		return nullptr;

	if(const UAssetManager* AssetManager = UAssetManager::GetIfInitialized())
	{
		return Cast<UMMGameData>(AssetManager->GetPrimaryAssetObject(CurrentGameDataAssetId));
	}
	
	return nullptr;	
}

void AMMGameMode::OnGameReady()
{
	bGameReady = true;
	InitializePlayers();
}

void AMMGameMode::InitializePlayers()
{
	for(AMMPlayerController* Player : SessionPlayers)
	{
		if(IsValid(Player) && Player->GetPawn() == nullptr)
		{
			if(const UMMGameData* GameData = GetGameData())
			{
				if(PlayerCanRestart(Player))
				{
					RestartPlayer(Player);
				}
			}		
		}
	}
}
