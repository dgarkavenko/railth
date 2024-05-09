// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/UI/MMJoinSessionWidget.h"
#include "CommonGameInstance.h"
#include "CommonSessionSubsystem.h"
#include "PrimaryGameLayout.h"
#include "Logging/StructuredLog.h"


void UMMJoinSessionWidget:: NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (RefreshButton)
	{
		RefreshButton->OnClicked(). AddUObject(this, &UMMJoinSessionWidget::StartSearch);
	}

	if (BackButton)
	{
		BackButton->OnClicked(). AddUObject(this, &UMMJoinSessionWidget::OnBackMenu);
	}
	
	SetSpinnerDisplay(false);
	NoSessionsDisplay->SetVisibility(ESlateVisibility::Collapsed);

}

void UMMJoinSessionWidget:: NativeOnActivated ()
{
	Super::NativeOnActivated();
	StartSearch();
}

UWidget* UMMJoinSessionWidget::NativeGetDesiredFocusTarget() const
{
	if(ListView)
	{
		return ListView;
	}
	
	return Super::NativeGetDesiredFocusTarget();
}

void UMMJoinSessionWidget::StartSearch()
{
	//UE_LOGFMT(LogTemp, Warning, "{Function} Start Search", __FUNCTIONW__);
	
	if(GetSearchInProgress() || !GetOwningPlayer() || !GetOwningPlayer()->GetWorld() || !ListView)
	{
		UE_LOGFMT(LogTemp, Display, "wow");
		return;
	}
	
	SetSearchingInProgress(true);
	NoSessionsDisplay->SetVisibility(ESlateVisibility::Collapsed);
	ListView->ClearListItems();
	
	const UCommonGameInstance* GameInstance = Cast<UCommonGameInstance>(
    		GetOwningPlayer()
    		->GetWorld()
    		->GetGameInstance());
    
    if (GameInstance == nullptr)
    	return;
    	
    if (UCommonSessionSubsystem* SessionSubsystem = GameInstance->GetSubsystem<UCommonSessionSubsystem>())
    {
    	if (auto* Request = SessionSubsystem->CreateOnlineSearchSessionRequest())
    	{
    		Request->OnSearchFinished.AddUObject(this, &UMMJoinSessionWidget::OnSessionSearchComplete, Request);
    		SessionSubsystem->FindSessions(GetOwningPlayer(), Request);
    	}
	    else
	    {
		    //error
	    }
    }
}

void UMMJoinSessionWidget::SetSearchingInProgress(bool bSearching)
{
	bSearchInProgress = bSearching;
	SetSpinnerDisplay(bSearching);
}

void UMMJoinSessionWidget::SetSpinnerDisplay(const bool bSpinnerState) const
{
	if(SpinnerDisplay)
	{
		SpinnerDisplay->SetVisibility(bSpinnerState ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}
}

void UMMJoinSessionWidget::OnSessionSearchComplete(bool bSucceeded, const FText& ErrorMessage,
	UCommonSession_SearchSessionRequest* SessionSearchRequest)
{
	SetSearchingInProgress(false);
	if(bSucceeded && SessionSearchRequest && SessionSearchRequest->Results.Num() > 0)
	{
		ListView->SetListItems(SessionSearchRequest->Results);
		ListView->SetUserFocus(GetOwningPlayer());
		NoSessionsDisplay->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		NoSessionsDisplay->SetVisibility(ESlateVisibility::Visible);
		//error
	}
}

void UMMJoinSessionWidget:: OnBackMenu()
{
	if(const UWorld* WorldContext = GetWorld())
	{
		if (UPrimaryGameLayout* RootLayout = UPrimaryGameLayout::GetPrimaryGameLayoutForPrimaryPlayer(WorldContext))
		{
			RootLayout->FindAndRemoveWidgetFromLayer(this);
		}
	}
}
