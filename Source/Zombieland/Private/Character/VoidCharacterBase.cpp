// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/VoidCharacterBase.h"

#include "Component/CombatComponent.h"


AVoidCharacterBase::AVoidCharacterBase()
{

	PrimaryActorTick.bCanEverTick = true;

	CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat"));

}

void AVoidCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (CombatComp)
	{
		CombatComp->SetCharacterOwner(this);
	}
}

void AVoidCharacterBase::PlayAttackMontage(const EWeaponType WeaponType)
{

	// TODO:: Choice with section name first attack or secondary
	if (WeaponMontages.IsEmpty() || !WeaponMontages.Contains(WeaponType)) return;

	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	{
		AnimInstance->Montage_Play(WeaponMontages[WeaponType]);
	}
}

void AVoidCharacterBase::PlayRechargeMontage()
{
	// TODO:: Choice which Weapon you want to charge
 	if (RechargeMontage)
	{
 		if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
 		{
 			AnimInstance->Montage_Play(RechargeMontage);
 		}
	}
}

void AVoidCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}



