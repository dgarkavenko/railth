// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\..\Public\Framework\Managers\MMGameState.h"

#include "..\..\..\Public\Framework\Data\MMGameData.h"
#include "Net/UnrealNetwork.h"

AMMGameState::AMMGameState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bReplicates = true;
}

void AMMGameState::GetLifetimeReplicatedProps( TArray<FLifetimeProperty> &OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ThisClass, GameData);
}

void AMMGameState::SetGameData(UMMGameData* NewGameData)
{
	if(!HasAuthority())
		return;
		
	if(NewGameData == nullptr)
		return;
	
	ensure(NewGameData);
	GameData = NewGameData;
	OnRep_GameData();
}

bool AMMGameState::ShouldShowMenu() const
{
	ensure(GameData);
	return GameData && GameData->bShowMenu;
}

TSoftClassPtr<UCommonActivatableWidget>& AMMGameState::GetMenuClass() const
{
	checkf(!GameData->MainMenuClass.IsNull(), TEXT("[%s]: MainMenuClass is null"), *GetPathNameSafe(GameData));
	return GameData->MainMenuClass;
}

void AMMGameState::OnRep_GameData()
{
	if(HasAuthority())
	{
		OnGameStateReady.Broadcast();
	}
}
