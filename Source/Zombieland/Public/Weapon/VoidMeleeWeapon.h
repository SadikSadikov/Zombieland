// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/VoidWeapon.h"
#include "VoidMeleeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIELAND_API AVoidMeleeWeapon : public AVoidWeapon
{
	GENERATED_BODY()

public:

	AVoidMeleeWeapon();
	void CreateSphereField(const FVector& TraceHitTarget);

	virtual void PrimaryAttack(const FVector& TraceHitTarget) override;

	virtual void SecondaryAttack(const FVector& TraceHitTarget) override;
	
	virtual bool CanAttack() override;

protected:

	UPROPERTY(EditAnywhere, Category = "Combat")
	float DamageRadius = 25.f;
	
	
};
