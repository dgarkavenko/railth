// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonGameInstance.h"
#include "MMGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERMENU_API UMMGameInstance : public UCommonGameInstance
{
	GENERATED_BODY()

	UMMGameInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
