// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/VoidWeapon.h"
#include "VoidProjectileWeapon.generated.h"

class AVoidProjectile;

UCLASS()
class ZOMBIELAND_API AVoidProjectileWeapon : public AVoidWeapon
{
	GENERATED_BODY()

public:

	virtual void Attack(const FVector& TraceHitTarget) override;

	virtual bool CanAttack() override;

	virtual bool CanRecharge() override;

	virtual void Recharge() override;


protected:

	virtual void BeginPlay() override;

	void UpdateAmmoValues();

	int32 AmountToReload() const;

	UPROPERTY(EditAnywhere, Category = "Combat|Gun")
	int32 CarriedAmmo = 30;

	UPROPERTY(EditAnywhere, Category = "Combat|Gun")
	int32 Ammo = 10;

	UPROPERTY(EditAnywhere, Category = "Combat|Gun")
	int MagCapacity = 10;

	void SpendRound();

	void AddAmmo(int32 Amount);

	virtual bool IsEmpty();
	
	virtual bool IsFull();

private:
	
	UPROPERTY(EditAnywhere, Category = "Properties")
	FName TipSocketName;

	UPROPERTY(EditAnywhere, Category = "Properties")
	TSubclassOf<AVoidProjectile> ProjectileClass;
	
	
};


