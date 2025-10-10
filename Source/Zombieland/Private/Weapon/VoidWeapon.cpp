// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/VoidWeapon.h"

AVoidWeapon::AVoidWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponStaticMesh"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(WeaponMesh);

	
	
}

float AVoidWeapon::GetDamage()
{
	return Damage;
}

void AVoidWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

float AVoidWeapon::GetAttackDelay(EAttackType InAttackType) const
{
	if (InAttackType == EAttackType::EAT_Primary)
	{
		return PrimaryAttackTimerDelay;
	}
	
	return SecondaryAttackTimerDelay;
}

void AVoidWeapon::PrimaryAttack(const FVector& TraceHitTarget)
{
	
}

void AVoidWeapon::SecondaryAttack(const FVector& TraceHitTarget)
{
}

void AVoidWeapon::Recharge()
{
}


bool AVoidWeapon::CanAttack()
{
	return false;
}

bool AVoidWeapon::CanRecharge()
{
	return false;
}






