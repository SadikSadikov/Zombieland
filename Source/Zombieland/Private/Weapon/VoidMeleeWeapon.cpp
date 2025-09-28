// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/VoidMeleeWeapon.h"

#include "Interaction/DamageableInterface.h"
#include "Kismet/KismetSystemLibrary.h"

AVoidMeleeWeapon::AVoidMeleeWeapon()
{
}

void AVoidMeleeWeapon::PrimaryAttack(const FVector& TraceHitTarget)
{
	Super::PrimaryAttack(TraceHitTarget);

	FName TargetTag = GetOwner()->ActorHasTag(FName("Player")) ? FName("Enemy") : FName("Player");
	ETraceTypeQuery TraceChanel = UEngineTypes::ConvertToTraceType(ECC_Visibility);
	TArray<FHitResult> Hits;

	// TODO:: Later remove DrawDebugTrace
	UKismetSystemLibrary::SphereTraceMulti(this, TraceHitTarget, TraceHitTarget, 25.f, TraceChanel,
		false, TArray<AActor*>(), EDrawDebugTrace::None, Hits, true);

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

	GEngine->AddOnScreenDebugMessage(-1, 2.F, FColor::Black, TEXT("Primary Attack"));
}

void AVoidMeleeWeapon::SecondaryAttack(const FVector& TraceHitTarget)
{
	Super::SecondaryAttack(TraceHitTarget);
}

bool AVoidMeleeWeapon::CanAttack()
{
	return true;
}
