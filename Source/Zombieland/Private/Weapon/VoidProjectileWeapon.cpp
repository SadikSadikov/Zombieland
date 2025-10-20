// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/VoidProjectileWeapon.h"
#include "Engine/StaticMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Projectile/VoidProjectile.h"


AVoidProjectileWeapon::AVoidProjectileWeapon()
{
	bUseTipSocket = true;
}

void AVoidProjectileWeapon::BeginPlay()
{
	Super::BeginPlay();

	// Initialize 
	Ammo = FMath::Clamp(Ammo, 0, MagCapacity);
}

void AVoidProjectileWeapon::SpawnProjectile(const FVector& TraceHitTarget, const TSubclassOf<AVoidProjectile>& ProjectileClass)
{
	if (ProjectileClass == nullptr) return;

	
	if (const UStaticMeshSocket* MeshSocket = GetWeaponMesh()->GetSocketByName(TipSocketName))
	{
		FTransform SocketTransform;
		MeshSocket->GetSocketTransform(SocketTransform, GetWeaponMesh());

		FVector ToTarget = TraceHitTarget - SocketTransform.GetLocation();
		FRotator TargetRotation = ToTarget.Rotation();
		//TargetRotation.Pitch = 0.f;
		
		APawn* InstigatorPawn = Cast<APawn>(GetOwner());
		
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		SpawnParameters.Owner = this;
		SpawnParameters.Instigator = InstigatorPawn;

		FVector SpawnLocation = SocketTransform.GetLocation();
		
		GetWorld()->SpawnActor<AVoidProjectile>(ProjectileClass, SpawnLocation, TargetRotation, SpawnParameters);

		if (!bUnlimitedAmmo)
		{
			SpendRound();
		}
		
		
		
	}
}

void AVoidProjectileWeapon::PrimaryAttack(const FVector& TraceHitTarget)
{
	Super::PrimaryAttack(TraceHitTarget);
	
	SpawnProjectile(TraceHitTarget, BulletProjectileClass);
}

void AVoidProjectileWeapon::SecondaryAttack(const FVector& TraceHitTarget)
{
	Super::SecondaryAttack(TraceHitTarget);

	SpawnProjectile(TraceHitTarget, RocketProjectileClass);
}

bool AVoidProjectileWeapon::CanAttack()
{
	return !IsEmpty();
}

void AVoidProjectileWeapon::SpendRound()
{
	Ammo = FMath::Clamp(Ammo - 1, 0, MagCapacity);
}

void AVoidProjectileWeapon::AddAmmo(int32 Amount)
{
	Ammo = FMath::Clamp(Ammo + Amount, 0, MagCapacity);
}

bool AVoidProjectileWeapon::IsEmpty()
{
	return Ammo <= 0;;
}

bool AVoidProjectileWeapon::IsFull()
{
	return Ammo == MagCapacity;
}

void AVoidProjectileWeapon::Recharge()
{
	UpdateAmmoValues();
}

void AVoidProjectileWeapon::UpdateAmmoValues()
{
	int32 ReloadAmount = AmountToReload();
	
	CarriedAmmo -= ReloadAmount;

	AddAmmo(ReloadAmount);
	
}

int32 AVoidProjectileWeapon::AmountToReload() const
{
	int32 RoomInMag = MagCapacity - Ammo;
	
	int32 Least = FMath::Min(RoomInMag, CarriedAmmo);
	return FMath::Clamp(RoomInMag, 0, Least);
	
}

bool AVoidProjectileWeapon::CanRecharge()
{
	return CarriedAmmo > 0 && !IsFull();
}







