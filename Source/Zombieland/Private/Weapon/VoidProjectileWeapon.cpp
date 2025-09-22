// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/VoidProjectileWeapon.h"
#include "Engine/StaticMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Projectile/VoidProjectile.h"


void AVoidProjectileWeapon::BeginPlay()
{
	Super::BeginPlay();

	// Initialize 
	Ammo = FMath::Clamp(Ammo, 0, MagCapacity);
}

void AVoidProjectileWeapon::PrimaryAttack(const FVector& TraceHitTarget)
{
	Super::PrimaryAttack(TraceHitTarget);

	

	if (const UStaticMeshSocket* MeshSocket = GetWeaponMesh()->GetSocketByName(TipSocketName))
	{
		FTransform SocketTransform;
		MeshSocket->GetSocketTransform(SocketTransform, GetWeaponMesh());

		if (MuzzleFlash)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, SocketTransform);
		}
		if (FireSound)
		{
			UGameplayStatics::SpawnSoundAtLocation(this, FireSound, SocketTransform.GetLocation());
		}

		FVector ToTarget = TraceHitTarget - SocketTransform.GetLocation();
		FRotator TargetRotation = ToTarget.Rotation();
		
		APawn* InstigatorPawn = Cast<APawn>(GetOwner());
		
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		SpawnParameters.Owner = this;
		SpawnParameters.Instigator = InstigatorPawn;
		
		GetWorld()->SpawnActor<AVoidProjectile>(ProjectileClass, SocketTransform.GetLocation(), TargetRotation, SpawnParameters);
		
		SpendRound();

		GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Green, FString::Printf(TEXT("Ammo - %d"), Ammo));
		
	}
}

void AVoidProjectileWeapon::SecondaryAttack(const FVector& TraceHitTarget)
{
	Super::SecondaryAttack(TraceHitTarget);

	// TODO:: Implement Secondary Attack
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







