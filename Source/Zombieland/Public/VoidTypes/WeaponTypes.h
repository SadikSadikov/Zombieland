#pragma once

#include "CoreMinimal.h"
#include "WeaponTypes.generated.h"

UENUM(BlueprintType)
enum class EWeaponType  : uint8
{
	EWT_Unarmed UMETA(DisplayName = "Unarmed"),
	EWT_Sword UMETA(DisplayName = "Sword"),
	EWT_Gun UMETA(DisplayName = "Gun"),

	EWT_Max UMETA(DisplayName = "DeafultMax")
	
};

UENUM(BlueprintType)
enum class EAttackType  : uint8
{
	EAT_Primary UMETA(DisplayName = "Primary"),
	EAT_Secondary UMETA(DisplayName = "Secondary"),

	EAT_Max UMETA(DisplayName = "DeafultMax")
	
};

USTRUCT(BlueprintType)
struct FAttackState
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Combat|Animation")
	UAnimMontage* PrimaryAttackMontage = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Combat|Animation")
	UAnimMontage* SecondaryAttackMontage = nullptr;
	
};