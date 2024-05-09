// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "MMMenuMultiplayerWidget.generated.h"

class UMMHostSessionWidget;
class UMMJoinSessionWidget;
class UMMButtonBase;
/**
 * 
 */
UCLASS(Abstract)
class MULTIPLAYERMENU_API UMMMenuMultiplayerWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:

	virtual void NativeOnInitialized() override;
	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	void AddWidgetToRootLayout(TSoftClassPtr<UCommonActivatableWidget> WidgetClass);

protected:

	UFUNCTION()
	void OnHostButtonClicked();

	UFUNCTION()
	void OnJoinButtonClicked();

	UFUNCTION()
	void OnExitButtonClicked();

	UPROPERTY (BlueprintReadOnly, meta = (BindWidget))
	UMMButtonBase* HostButton;
	
	UPROPERTY (BlueprintReadOnly, meta = (BindWidget))
	UMMButtonBase* JoinButton;

	UPROPERTY (BlueprintReadOnly, meta = (BindWidget))
	UMMButtonBase* ExitButton;

	UPROPERTY (BlueprintReadWrite, EditDefaultsOnly)
	TSoftClassPtr<UMMHostSessionWidget> HostWidgetClass;
	
	UPROPERTY (BlueprintReadWrite, EditDefaultsOnly)
	TSoftClassPtr<UMMJoinSessionWidget> JoinWidgetClass;
};
