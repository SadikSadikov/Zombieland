// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/Weapon.h"
#include "CombatComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZOMBIELAND_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UCombatComponent();

	void Attack(EAttackType AttackType);

protected:
	
	virtual void BeginPlay() override;

	void FireGun();

private:

	UPROPERTY()
	TObjectPtr<AWeapon> EquippedWeapon;

	UPROPERTY()
	TObjectPtr<AWeapon> SecondaryWeapon;
	

		
};
