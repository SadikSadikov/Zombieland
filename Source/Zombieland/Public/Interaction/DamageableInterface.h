// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "VoidTypes/DamageInfo.h"
#include "DamageableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDamageableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ZOMBIELAND_API IDamageableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual float GetHealth() = 0;

	virtual float GetMaxHealth() = 0;

	virtual void Heal(float Amount) = 0;

	virtual void TakeDamage(const FDamageInfo& DamageInfo) = 0;

	
};
