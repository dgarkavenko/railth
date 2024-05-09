#include "Framework\UI\MMButtonBase.h"


void UMMButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();
	InitializeCustomButtonData();
}

void UMMButtonBase::InitializeCustomButtonData()
{
	ApplyMaterial();
	UpdateButtonText();
	SetButtonSettings();   
}

void UMMButtonBase::SetButtonSettings()
{
	if(!IsValid(Border))
		return;

	UMaterialInstanceDynamic* MaterialInstance = Border->GetDynamicMaterial();

	if(!IsValid(MaterialInstance))
		return;

	if(bOverride_Texture_Alpha)
	{
		MaterialInstance->SetScalarParameterValue("TextureAlpha", TextureAlpha);
		MaterialInstance->SetScalarParameterValue("TextureAlphaHover", TextureAlphaHover);
	}

	if(bOverride_Texture_Scale)
	{
		MaterialInstance->SetScalarParameterValue("TexScale", TextureScale);
		MaterialInstance->SetScalarParameterValue("TexScaleHover", TextureScaleHover);
	}

	if(bOverride_Texture_Shift)
	{
		MaterialInstance->SetScalarParameterValue("Shift_X", TextureShiftX);
		MaterialInstance->SetScalarParameterValue("Shift_Y", TextureShiftY);
	}

	if(IsValid(Texture))
	{
		MaterialInstance->SetTextureParameterValue("Texture", Texture);
	}
}

void UMMButtonBase::SetButtonText(FText InText)
{
	bOverride_ButtonText = InText.IsEmpty();
	Text = InText;
	UpdateButtonText();
}

void UMMButtonBase::UpdateButtonText()
{
	if (!IsValid(TextBlock))        
		return;        

	TextBlock->SetText(Text);
}


void UMMButtonBase::ApplyMaterial()
{
	if(!IsValid(Border) || !IsValid(Material))
		return;

	Border->SetBrushFromMaterial(Material);
}
    