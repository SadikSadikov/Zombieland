// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/VoidMeleeWeapon.h"

#include "Engine/StaticMeshSocket.h"
#include "Interaction/DamageableInterface.h"
#include "Kismet/KismetSystemLibrary.h"

AVoidMeleeWeapon::AVoidMeleeWeapon()
{
}

void AVoidMeleeWeapon::CreateSphereField(const FVector& TraceHitTarget)
{
	FName TargetTag = GetOwner()->ActorHasTag(FName("Player")) ? FName("Enemy") : FName("Player");
	ETraceTypeQuery TraceChanel = UEngineTypes::ConvertToTraceType(ECC_Visibility);
	TArray<FHitResult> Hits;
	
	UKismetSystemLibrary::SphereTraceMulti(this, TraceHitTarget, TraceHitTarget, DamageRadius, TraceChanel,
	                                       false, TArray<AActor*>(), EDrawDebugTrace::ForDuration, Hits, true);

	for (const FHitResult& Hit : Hits)
	{
		if (Hit.GetActor()->ActorHasTag(TargetTag))
		{
			if (IDamageableInterface* DamagableActor = Cast<IDamageableInterface>(Hit.GetActor()))
			{
				FDamageInfo DamageInfo;
				DamageInfo.Amount = GetDamage();
				DamageInfo.DamageCauser = Hit.GetActor();
				
				DamagableActor->TakeDamage(DamageInfo);
			}
		}
	}
}

void AVoidMeleeWeapon::PrimaryAttack(const FVector& TraceHitTarget)
{
	Super::PrimaryAttack(TraceHitTarget);
	
	// When WeaponMesh is set and Have TipSocket
	if (const UStaticMeshSocket* MeshSocket = GetWeaponMesh()->GetSocketByName(TipSocketName))
	{
		FTransform SocketTransform;
		MeshSocket->GetSocketTransform(SocketTransform, GetWeaponMesh());

		CreateSphereField(SocketTransform.GetLocation());
	}
	// If you do not have Socket And Mesh Use TraceHitTarget for Sphere Center Loc
	else
	{
		CreateSphereField(TraceHitTarget);
	}
	

	
	
}

void AVoidMeleeWeapon::SecondaryAttack(const FVector& TraceHitTarget)
{
	Super::SecondaryAttack(TraceHitTarget);
}

bool AVoidMeleeWeapon::CanAttack()
{
	return true;
}
