#pragma once

#include "NativeGameplayTags.h"

#define MM_DATA_ASSET_TYPE_GAMEDATA			FName(TEXT("GameData"))
#define MM_DATA_ASSET_TYPE_GAMEDATA_DEFAULT	FName(TEXT("DA_GameData_Default"))


#define MM_SETTINGS_GAMEMODE				TEXT("GAMEMODE")

#define MM_DATA_ASSET_BUNDLE_GAME			FName("GameBundle")

namespace UILayerTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_UI_LAYER_GAME);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_UI_LAYER_GAMEMENU);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_UI_LAYER_MENU);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_UI_LAYER_MODAL);
}
