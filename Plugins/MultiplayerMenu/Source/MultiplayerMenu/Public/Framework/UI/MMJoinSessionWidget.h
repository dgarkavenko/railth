// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "MMButtonBase.h"
#include "CommonListView.h" 
#include "MMJoinSessionWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class MULTIPLAYERMENU_API UMMJoinSessionWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnActivated() override;
	virtual UWidget* NativeGetDesiredFocusTarget() const override;

protected:

	UFUNCTION()
	void StartSearch();

	void SetSearchingInProgress(bool bSearching);
	bool GetSearchInProgress() const {return bSearchInProgress; }
	
	void SetSpinnerDisplay(const bool bSpinnerState) const;

	UFUNCTION()
	void OnSessionSearchComplete(bool bSucceeded, const FText& ErrorMessage, UCommonSession_SearchSessionRequest* SessionSearchRequest);

	UFUNCTION()
	void OnBackMenu();

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCommonListView* ListView;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UMMButtonBase* RefreshButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UMMButtonBase* BackButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCommonBorder* NoSessionsDisplay;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCommonBorder* SpinnerDisplay;

	UPROPERTY()
	bool bSearchInProgress = false;
	
};
