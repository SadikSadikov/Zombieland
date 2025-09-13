// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/VoidWeapon.h"

AVoidWeapon::AVoidWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponStaticMesh"));
	SetRootComponent(WeaponMesh);



}

void AVoidWeapon::Attack()
{

	
}




void AVoidWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}



