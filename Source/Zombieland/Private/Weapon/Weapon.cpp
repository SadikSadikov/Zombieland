// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Weapon.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponStaticMesh"));
	SetRootComponent(WeaponStaticMesh);

	WeaponSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponSkeletalMesh"));
	WeaponSkeletalMesh->SetupAttachment(GetRootComponent());

}

void AWeapon::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (bUseSkeletalMesh)
	{
		WeaponSkeletalMesh->SetVisibility(true);
		WeaponStaticMesh->SetVisibility(false);
		SetRootComponent(WeaponSkeletalMesh);
	}
	else
	{
		WeaponStaticMesh->SetVisibility(true);
		WeaponSkeletalMesh->SetVisibility(false);
		SetRootComponent(WeaponStaticMesh);
	}

	
}

void AWeapon::Attack()
{
	if (AttackAnimation && bUseSkeletalMesh)
	{
		WeaponSkeletalMesh->PlayAnimation(AttackAnimation, false);
	}


	// This class is generic for waepons word, gun not only gun
	// TODO:: Check here are we have anough ammo and update HUD
}




void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


