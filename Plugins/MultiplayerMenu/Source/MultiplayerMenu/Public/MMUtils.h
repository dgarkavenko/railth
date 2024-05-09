#pragma once

#include <type_traits>

class MULTIPLAYERMENU_API MMUtils
{
	
public:
	template<typename TEnum>
	static void IncrementEnum(TEnum& enumValue, TEnum EnumMax)
	{
		static_assert(std::is_enum_v<TEnum>, "TEnum must be an enumeration type.");
		using UnderlyingType = std::underlying_type_t<TEnum>;
		UnderlyingType currentValue = static_cast<UnderlyingType>(enumValue);
		UnderlyingType enumMaxValue = static_cast<UnderlyingType>(EnumMax);

		currentValue = (currentValue + 1) % enumMaxValue;
		enumValue = static_cast<TEnum>(currentValue);
	}
	
};