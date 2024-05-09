#pragma once

#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "CommonBorder.h"
#include "MMButtonBase.generated.h"

UCLASS(Abstract)
class MULTIPLAYERMENU_API UMMButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCommonTextBlock* TextBlock;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCommonBorder* Border;

	UPROPERTY(EditAnywhere, Category="Button", meta=(InlineEditConditionToggle))
	bool bOverride_ButtonText;

	UPROPERTY(EditAnywhere, Category="Button", meta=(editcondition="bOverride_ButtonText"))
	FText Text;

	UPROPERTY(EditAnywhere, Category="Button")
	UMaterialInstance* Material;

	UPROPERTY(EditAnywhere, Category="Button|Texture")
	UTexture2D* Texture;

	UPROPERTY(EditAnywhere, Category="Button", meta=(InlineEditConditionToggle))
	bool bOverride_Texture_Alpha;

	UPROPERTY(EditAnywhere, Category="Button", meta=(InlineEditConditionToggle))
	bool bOverride_Texture_Scale;

	UPROPERTY(EditAnywhere, Category="Button", meta=(InlineEditConditionToggle))
	bool bOverride_Texture_Shift;

	UPROPERTY(EditAnywhere, Category="Button|Texture", meta=(editcondition="bOverride_Texture_Alpha"))
	float TextureAlpha = 1.f;

	UPROPERTY(EditAnywhere, Category="Button|Texture", meta=(editcondition="bOverride_Texture_Alpha"))
	float TextureAlphaHover = 0.9f;

	UPROPERTY(EditAnywhere, Category="Button|Texture", meta=(editcondition="bOverride_Texture_Scale"))
	float TextureScale = 1.f;

	UPROPERTY(EditAnywhere, Category="Button|Texture", meta=(editcondition="bOverride_Texture_Scale"))
	float TextureScaleHover = 0.9f;

	UPROPERTY(EditAnywhere, Category="Button|Texture", meta=(editcondition="bOverride_Texture_Shift"))
	float TextureShiftX;

	UPROPERTY(EditAnywhere, Category="Button|Texture", meta=(editcondition="bOverride_Texture_Shift"))
	float TextureShiftY;

public:

	virtual void NativePreConstruct() override;

	void InitializeCustomButtonData();

	UFUNCTION(BlueprintCallable)
	void SetButtonSettings();

	UFUNCTION(BlueprintCallable)
	void SetButtonText(FText InText);

	UFUNCTION(BlueprintCallable)
	void ApplyMaterial();

	UFUNCTION(BlueprintCallable)
	void UpdateButtonText();

	
};
