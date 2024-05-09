// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "CommonSessionSubsystem.h"
#include "CommonUserSubsystem.h"
#include "MMHostSessionWidget.generated.h"


class UCommonTextBlock;
enum class ECommonSessionOnlineMode : uint8;
class UMMButtonBase;
class UMMButtonGameWidget;
class UMMGameDisplayListWidget;

UENUM()
enum class EHostSettings : uint8
{
	A,
	B,
	C
};

UCLASS(Abstract)
class MULTIPLAYERMENU_API UMMHostSessionWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
public:

	UFUNCTION()
	void OnNetModeClicked();

	UFUNCTION()
	void OnSettingsButtonClicked();
	UFUNCTION()
	void OnUserLogin(const UCommonUserInfo* UserInfo, bool bSuccess, FText Error, ECommonUserPrivilege RequestedPrivilege, ECommonUserOnlineContext OnlineContext);
	void OnSessionCreated(const FOnlineResultInformation& OnlineResultInformation);
	UCommonSession_HostSessionRequest* CreateHostSessionRequest();
	void HostSession();

	UFUNCTION()
	void OnLaunchButtonClicked();

	UFUNCTION()
	void OnBackButtonClicked();

	UFUNCTION()
	void OnGameListCreated();

	UFUNCTION()
	void OnGameSelected(const FPrimaryAssetId& SelectedGameDataId);
	
	virtual void NativeOnInitialized() override;

protected:
	void InitTextDisplays() const;

	UPROPERTY()
	FPrimaryAssetId GameDataId;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UMMGameDisplayListWidget* GameList;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCommonTextBlock* SelectedGameTitleText;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UMMButtonBase* LaunchButton;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UMMButtonBase* BackButton;

	UPROPERTY()
	EHostSettings HostSettings;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCommonTextBlock* GameSettingsText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UMMButtonBase* ChangeSettingsButton;

	UPROPERTY()
	ECommonSessionOnlineMode NetMode;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCommonTextBlock* NetModeText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UMMButtonBase* NetModeButton;
	

};
