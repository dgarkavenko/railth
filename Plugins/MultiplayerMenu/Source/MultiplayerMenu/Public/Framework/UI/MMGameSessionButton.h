// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MMButtonBase.h"
#include "MMGameSessionButton.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class MULTIPLAYERMENU_API UMMGameSessionButton : public UMMButtonBase
{
	GENERATED_BODY()

public:
	void SetTextDisplays(const FText& Game, const FText& Map, const FText& Ping, const FText& PlayerCount, const FText& MaxPlayerCount);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCommonTextBlock* MapText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCommonTextBlock* PingText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCommonTextBlock* PlayerCountText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCommonTextBlock* MaxPlayerCountText;

};
