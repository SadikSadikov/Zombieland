// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/VoidWeapon.h"

AVoidWeapon::AVoidWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponStaticMesh"));
	SetRootComponent(WeaponMesh);



}

void AVoidWeapon::Attack(const FVector& TraceHitTarget)
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

void AVoidWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}




