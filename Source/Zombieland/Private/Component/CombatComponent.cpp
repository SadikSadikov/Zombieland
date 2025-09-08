// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/CombatComponent.h"


UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UCombatComponent::Attack(EAttackType AttackType)
{
	if (EquippedWeapon)
	{
		switch (EquippedWeapon->WeaponType)
		{
		case EWeaponType::EWT_Unarmed:
			// TODO:: Make unarmed attack
			break;

		case EWeaponType::EWT_Sword:
			// TODO:: Make sword attack
			break;

		case EWeaponType::EWT_Gun:
			if (AttackType == EAttackType::EAT_Primary)
			{
				
			}
			else if (AttackType == EAttackType::EAT_Secondary)
			{
				
			}
			break;
			
		default: ;
		}
	}
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void UCombatComponent::FireGun()
{
	// TODO:: Check if character is Unoccupied(not plying animation something like this) CombatState
	// Play animation (firing a weapon)

	
	EquippedWeapon->Attack();
}


