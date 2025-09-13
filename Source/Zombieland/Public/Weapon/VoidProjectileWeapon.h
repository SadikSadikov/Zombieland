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

	virtual void Attack() override;

protected:

private:

	/* Socket need to point forward (X axis) this is important because in this way you can shoot in the right way */
	UPROPERTY(EditAnywhere, Category = "Properties")
	FName TipSocketName;

	UPROPERTY(EditAnywhere, Category = "Properties")
	TSubclassOf<AVoidProjectile> ProjectileClass;
	
	
};
