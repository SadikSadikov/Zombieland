// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/CombatComponent.h"

#include "Character/VoidCharacterBase.h"
#include "Engine/SkeletalMeshSocket.h"


UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnDefaultWeapon();
	
	
}

void UCombatComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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
	
	if (CharacterOwner && CanAttack())
	{
		if (CharacterOwner->Implements<UCombatInterface>())
		{
			ICombatInterface::Execute_UpdateFacingTarget(GetOwner(), CharacterOwner->GetHitTarget());
		}
		
		CombatState = ECombatState::ECS_Attacking;
		CharacterOwner->PlayAttackMontage(EquippedWeapon->GetWeaponType(), AttackType);
		
	}
}

bool UCombatComponent::CanAttack()
{
	if (EquippedWeapon == nullptr) return false;

	return EquippedWeapon->CanAttack() && CombatState == ECombatState::ECS_Unoccupied;
}

void UCombatComponent::AttackImpact(EAttackType AttackType)
{
	if (AttackType == EAttackType::EAT_Primary)
	{
		EquippedWeapon->PrimaryAttack(CharacterOwner->GetHitTarget());
	}
	else if (AttackType == EAttackType::EAT_Secondary)
	{
		EquippedWeapon->SecondaryAttack(CharacterOwner->GetHitTarget());
	}

	StartAttackTimer();
}

void UCombatComponent::StartAttackTimer()
{
	if (CharacterOwner == nullptr || EquippedWeapon == nullptr) return;

	CharacterOwner->GetWorldTimerManager().SetTimer(AttackTimer,
		this,
		&UCombatComponent::AttackTimerFinished,
		EquippedWeapon->GetAttackDelay());
}

void UCombatComponent::AttackTimerFinished()
{
	if (EquippedWeapon == nullptr) return;
	CombatState = ECombatState::ECS_Unoccupied;

	RechargeEmptyWeapon();
}

void UCombatComponent::RechargeEmptyWeapon()
{
	if (EquippedWeapon && !EquippedWeapon->CanAttack())
	{
		Recharge();
	}
}





void UCombatComponent::Recharge()
{
	if (CanRecharge())
	{
		CombatState = ECombatState::ECS_Recharging;
		CharacterOwner->PlayRechargeMontage();
	}
}

void UCombatComponent::RechargeFinished()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->Recharge();
	}
	CombatState = ECombatState::ECS_Unoccupied;
}

bool UCombatComponent::CanRecharge()
{
	return EquippedWeapon && EquippedWeapon->CanRecharge() && CombatState == ECombatState::ECS_Unoccupied;
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


