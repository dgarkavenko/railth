// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameUIManagerSubsystem.h"
#include "MMGameUIManager.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERMENU_API UMMGameUIManagerSubsystem : public UGameUIManagerSubsystem
{
	GENERATED_BODY()

public:
	UMMGameUIManagerSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	bool Tick(float DeltaTime);
	void SyncRootLayoutVisibilityToShowHUD();

	FTSTicker::FDelegateHandle TickHandle;
	
};
