// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/VoidMeleeWeapon.h"
#include "Engine/StaticMeshSocket.h"
#include "Interaction/DamageableInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

AVoidMeleeWeapon::AVoidMeleeWeapon()
{

}

void AVoidMeleeWeapon::CreateSphereField(const FVector& TraceHitTarget, float Radius)
{
	FName TargetTag = GetOwner()->ActorHasTag(FName("Player")) ? FName("Enemy") : FName("Player");
	ETraceTypeQuery TraceChanel = UEngineTypes::ConvertToTraceType(ECC_Visibility);
	TArray<FHitResult> Hits;
	
	UKismetSystemLibrary::SphereTraceMulti(this, TraceHitTarget, TraceHitTarget, Radius, TraceChanel,
	                                       false, TArray<AActor*>(), EDrawDebugTrace::None, Hits, true);

	for (const FHitResult& Hit : Hits)
	{
		if (Hit.GetActor()->ActorHasTag(TargetTag))
		{
			if (IDamageableInterface* DamagableActor = Cast<IDamageableInterface>(Hit.GetActor()))
			{

				FDamageProps DamageProps = GetDamage();
				
				FDamageInfo DamageInfo;
				DamageInfo.Amount = DamageProps.BaseDamage;
				DamageInfo.DamageCauser = Hit.GetActor();
				
				DamagableActor->TakeDamage(DamageInfo);

				if (ImpactSound)
				{
					UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
				}
			}
		}
	}

	
}

void AVoidMeleeWeapon::PrimaryAttack(const FVector& TraceHitTarget)
{
	Super::PrimaryAttack(TraceHitTarget);

	float RandValue = FMath::RandRange(0.f,1.f);

	if (RandValue <= CameraShakePercentage / 100.f)
	{
		if (CameraShakeClass && bUseCameraShake)
		{
			bool bIsPlayedCameraShake = false;
			if (GetInstigator())
			{
				if (APlayerController* PlayerController = Cast<APlayerController>(GetInstigator()->GetController()))
				{
					if (PlayerController->PlayerCameraManager)
					{
						PlayerController->PlayerCameraManager->StartCameraShake(CameraShakeClass);
						bIsPlayedCameraShake = true;
					}
				}
			}
			if (!bIsPlayedCameraShake)
			{
				UGameplayStatics::PlayWorldCameraShake(GetWorld(), CameraShakeClass, GetActorLocation(), 100000.f, 200000.f);
			}
			
		}
	}
	
	
	// When WeaponMesh is set and Have TipSocket
	if (bUseTipSocket)
	{
		if (const UStaticMeshSocket* MeshSocket = GetWeaponMesh()->GetSocketByName(TipSocketName))
		{
			FTransform SocketTransform;
			MeshSocket->GetSocketTransform(SocketTransform, GetWeaponMesh());

			CreateSphereField(SocketTransform.GetLocation(), PrimaryDamageRadius);
		}
	}
	
	// If you do not have Socket And Mesh Use TraceHitTarget for Sphere Center Loc
	else
	{
		CreateSphereField(TraceHitTarget, PrimaryDamageRadius);
	}
	

	
	
}

void AVoidMeleeWeapon::SecondaryAttack(const FVector& TraceHitTarget)
{
	Super::SecondaryAttack(TraceHitTarget);

	float RandValue = FMath::RandRange(0.f,1.f);

	if (RandValue <= CameraShakePercentage / 100.f)
	{
		if (CameraShakeClass && bUseCameraShake)
		{
			bool bIsPlayedCameraShake = false;
			if (GetInstigator())
			{
				if (APlayerController* PlayerController = Cast<APlayerController>(GetInstigator()->GetController()))
				{
					if (PlayerController->PlayerCameraManager)
					{
						PlayerController->PlayerCameraManager->StartCameraShake(CameraShakeClass);
						bIsPlayedCameraShake = true;
					}
				}
			}
			if (!bIsPlayedCameraShake)
			{
				UGameplayStatics::PlayWorldCameraShake(GetWorld(), CameraShakeClass, GetActorLocation(), 500.f, 1000.f);
			}
			
		}
	}
	
	// When WeaponMesh is set and Have TipSocket
	if (bUseTipSocket)
	{
		if (const UStaticMeshSocket* MeshSocket = GetWeaponMesh()->GetSocketByName(TipSocketName))
		{
			FTransform SocketTransform;
			MeshSocket->GetSocketTransform(SocketTransform, GetWeaponMesh());

			CreateSphereField(SocketTransform.GetLocation(), SecondaryDamageRadius);
		}
	}
	
	// If you do not have Socket And Mesh Use TraceHitTarget for Sphere Center Loc
	else
	{
		CreateSphereField(TraceHitTarget, SecondaryDamageRadius);
	}
}

bool AVoidMeleeWeapon::CanAttack()
{
	return true;
}

void AVoidMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

