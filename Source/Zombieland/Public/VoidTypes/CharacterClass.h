#pragma once

UENUM(BlueprintType, BlueprintType)
enum class ECharacterClass  : uint8
{
	ECC_Warrior UMETA(DisplayName = "Warrior"),
	ECC_Ranged UMETA(DisplayName = "Ranged"),
	ECC_Hybrid UMETA(DisplayName = "Hybrid"),

	ECC_Max UMETA(DisplayName = "DeafultMax")
	
};
