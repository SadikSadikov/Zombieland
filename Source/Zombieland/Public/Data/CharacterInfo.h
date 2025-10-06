// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "VoidTypes/CharacterClass.h"
#include "VoidTypes/WeaponTypes.h"
#include "CharacterInfo.generated.h"

USTRUCT(BlueprintType)
struct FCharacterCombatInfo
{
	GENERATED_BODY()

	
	
};

USTRUCT(BlueprintType)
struct FWeaponInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<EAttackType, UAnimMontage*> WeaponInfo;

	// Per weapon type and attack type
	UPROPERTY(EditDefaultsOnly, Category = "Combat|Animation")
	TObjectPtr<UAnimMontage> RechargeMontage;
	
};

UCLASS()
class ZOMBIELAND_API UCharacterInfo : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECharacterClass CharacterClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<EWeaponType, FWeaponInfo> Weapons;

	bool bCanCombo;

	int32 ComboCount;
	
	

	
	
};
