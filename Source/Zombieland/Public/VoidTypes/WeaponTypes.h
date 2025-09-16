#pragma once

UENUM(BlueprintType)
enum class EWeaponType  : uint8
{
	EWT_Unarmed UMETA(DisplayName = "Unarmed"),
	EWT_Sword UMETA(DisplayName = "Sword"),
	EWT_Gun UMETA(DisplayName = "Gun"),

	EWT_Max UMETA(DisplayName = "DeafultMax")
	
};