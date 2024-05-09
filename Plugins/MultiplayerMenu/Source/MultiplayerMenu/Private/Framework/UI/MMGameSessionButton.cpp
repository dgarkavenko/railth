// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UI/MMGameSessionButton.h"

void UMMGameSessionButton::SetTextDisplays(const FText& Game, const FText& Map, const FText& Ping,
	const FText& PlayerCount, const FText& MaxPlayerCount)
{
	SetButtonText(Game);

	if(MapText)
		MapText->SetText(Map);

	if(PingText)
		PingText->SetText(Ping);

	if(PlayerCountText)
		PlayerCountText->SetText(PlayerCount);

	if(MaxPlayerCountText)
		MaxPlayerCountText->SetText(MaxPlayerCount);	
}
