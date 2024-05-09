// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "MMPlayerController.generated.h"

class UCommonActivatableWidget;
/**
 * 
 */
UCLASS()
class MULTIPLAYERMENU_API AMMPlayerController : public ACommonPlayerController
{
	GENERATED_BODY()

public:
	AMMPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void OnPossess(APawn* InPawn) override;
	void ShowMenu(const TSoftClassPtr<UCommonActivatableWidget>& MenuClass);

};
