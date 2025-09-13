// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/VoidProjectileWeapon.h"
#include "Engine/StaticMeshSocket.h"
#include "Weapon/Projectile/VoidProjectile.h"

void AVoidProjectileWeapon::Attack()
{
	Super::Attack();

	// TODO:: Check here are we have enough ammo and update HUD
	
	

	if (const UStaticMeshSocket* MeshSocket = GetWeaponMesh()->GetSocketByName(TipSocketName))
	{
		FTransform SocketTransform;
		MeshSocket->GetSocketTransform(SocketTransform, GetWeaponMesh());
		
		APawn* InstigatorPawn = Cast<APawn>(GetOwner());
		
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = GetOwner();
		SpawnParameters.Instigator = InstigatorPawn;
		
		GetWorld()->SpawnActor<AVoidProjectile>(ProjectileClass, SocketTransform.GetLocation(), SocketTransform.Rotator(), SpawnParameters);
		
	}
}
