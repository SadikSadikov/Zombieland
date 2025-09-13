// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/CombatComponent.h"

#include "Character/VoidCharacterBase.h"
#include "Engine/SkeletalMeshSocket.h"


UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UCombatComponent::EquipWeapon(AVoidWeapon* WeaponToEquip)
{
	if (WeaponToEquip == nullptr) return;

	if (EquippedWeapon != nullptr && SecondaryWeapon == nullptr)
	{
		EquipSecondaryWeapon(WeaponToEquip);
	}
	else
	{
		EquipPrimaryWeapon(WeaponToEquip);
	}
		
}

void UCombatComponent::Attack(EAttackType AttackType)
{
	
	if (EquippedWeapon)
	{
		PlayAttackMontage(EquippedWeapon->WeaponType);
		
		switch (EquippedWeapon->WeaponType)
		{
		case EWeaponType::EWT_Unarmed:
			// TODO:: Make unarmed attack
			break;

		case EWeaponType::EWT_Sword:
			// TODO:: Make sword attack
			break;

		case EWeaponType::EWT_Gun:

			FireGun();

			
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

	SpawnDefaultWeapon();
	
	
}

void UCombatComponent::FireGun()
{
	// TODO:: Check if character is Unoccupied(not plying animation something like this) CombatState
	// Play animation (firing a weapon)

	
	EquippedWeapon->Attack();
}

void UCombatComponent::EquipPrimaryWeapon(AVoidWeapon* WeaponToEquip)
{
	EquippedWeapon = WeaponToEquip;
	EquippedWeapon->SetOwner(GetOwner());
	AttachWeaponToRightHand(EquippedWeapon);
	
}

void UCombatComponent::EquipSecondaryWeapon(AVoidWeapon* WeaponToEquip)
{
	SecondaryWeapon = WeaponToEquip;
	SecondaryWeapon->SetOwner(GetOwner());
}

void UCombatComponent::AttachWeaponToRightHand(AActor* WeaponToAttach)
{
	if (CharacterOwner == nullptr || CharacterOwner->GetMesh() == nullptr || WeaponToAttach == nullptr ) return;

	if (const USkeletalMeshSocket* MeshSocket = CharacterOwner->GetMesh()->GetSocketByName(FName("RightHandSocket")))
	{
		MeshSocket->AttachActor(WeaponToAttach, CharacterOwner->GetMesh());
	}
}

void UCombatComponent::PlayAttackMontage(const EWeaponType WeaponType)
{
	if (WeaponMontages.IsEmpty() || !WeaponMontages.Contains(WeaponType)) return;

	if (UAnimInstance* AnimInstance = CharacterOwner->GetMesh()->GetAnimInstance())
	{
		AnimInstance->Montage_Play(WeaponMontages[WeaponType]);
	}

}

void UCombatComponent::SpawnDefaultWeapon()
{

	if (GetWorld() && DefaultWeaponClass)
	{
		if (AVoidWeapon* Weapon = GetWorld()->SpawnActor<AVoidWeapon>(DefaultWeaponClass))
		{
			EquipWeapon(Weapon);
		}
	
	}
}


