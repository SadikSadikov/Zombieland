// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Projectile/VoidProjectile.h"

#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Interaction/DamageableInterface.h"
#include "Interaction/WeaponInterface.h"


AVoidProjectile::AVoidProjectile()
{

	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(BoxComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMeshComponent->SetupAttachment(GetRootComponent());
	

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->bRotationFollowsVelocity = true;
	MovementComponent->InitialSpeed = InitialSpeed;
	MovementComponent->MaxSpeed = InitialSpeed;
	

}

void AVoidProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (TracerParticle)
	{
		TracerComponent = UGameplayStatics::SpawnEmitterAttached(TracerParticle, GetRootComponent(),
			FName(), GetActorLocation(), GetActorRotation(),
			EAttachLocation::Type::KeepWorldPosition);
	}

	SpawnTrailSystem();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AVoidProjectile::OnHit);
	
}

void AVoidProjectile::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetInstigator()) return;


	if (ProjectileType == EProjectileType::EPT_Bullet)
	{

		if (IDamageableInterface* Damageable = Cast<IDamageableInterface>(OtherActor))
		{
			if (IWeaponInterface* WeaponInterface = Cast<IWeaponInterface>(GetOwner()))
			{

				FDamageProps DamageProps = WeaponInterface->GetDamage();
				
				FDamageInfo DamageInfo;
				DamageInfo.Amount = DamageProps.BaseDamage;
				DamageInfo.DamageCauser = OtherActor;
			
				Damageable->TakeDamage(DamageInfo);
				
			}
		}
		
	}
	else if (ProjectileType == EProjectileType::EPT_Rocket)
	{
		if (IWeaponInterface* WeaponInterface = Cast<IWeaponInterface>(GetOwner()))
		{
			FDamageProps DamageProps = WeaponInterface->GetDamage();

			TSet<AActor*> DamagedActors;

			ETraceTypeQuery DamageQuery = UEngineTypes::ConvertToTraceType(ECC_Pawn);
			
			TArray<AActor*> IgnoreActors;
			IgnoreActors.Add(GetInstigator());
			IgnoreActors.Add(GetOwner());
			IgnoreActors.Add(this);

			TArray<FHitResult> InnerHits;

			TArray<FHitResult> OuterHits;
			
			UKismetSystemLibrary::SphereTraceMulti(GetWorld(), GetActorLocation(), GetActorLocation(),
				DamageProps.InnerRadius, DamageQuery, false, IgnoreActors, EDrawDebugTrace::None, InnerHits, true);

			UKismetSystemLibrary::SphereTraceMulti(GetWorld(), GetActorLocation(), GetActorLocation(),
				DamageProps.OuterRadius, DamageQuery, false, IgnoreActors, EDrawDebugTrace::None, OuterHits, true);

			for (FHitResult HitResult : InnerHits)
			{
				if (IDamageableInterface* Damageable = Cast<IDamageableInterface>(HitResult.GetActor()))
				{

					if (!HitResult.GetActor() || DamagedActors.Contains(HitResult.GetActor()))
					{
						continue;
					}
					
					FDamageInfo DamageInfo;
					DamageInfo.Amount = DamageProps.BaseDamage;
					DamageInfo.DamageCauser = GetInstigator();
					
					Damageable->TakeDamage(DamageInfo);
					
					DamagedActors.Add(HitResult.GetActor());
				}
			}

			for (FHitResult HitResult : OuterHits)
			{
				if (IDamageableInterface* Damageable = Cast<IDamageableInterface>(HitResult.GetActor()))
				{
					if (!HitResult.GetActor() || DamagedActors.Contains(HitResult.GetActor()))
					{
						continue;
					}
					
					float Alpha  = (GetDistanceTo(HitResult.GetActor()) - DamageProps.InnerRadius) / (DamageProps.OuterRadius - DamageProps.InnerRadius);
					Alpha = FMath::Clamp(Alpha, 0.0f, 1.0f);

					/* Linear Interp */
					float DamageCalc = Alpha * DamageProps.MinDamage + (1.f - Alpha) * DamageProps.BaseDamage;

					/* You can use this is exacly same only added DamageFalloff for controlling the curve*/
					//float DamageCalc = FMath::Lerp(DamageProps.BaseDamage, DamageProps.MinDamage, FMath::Pow(Alpha, DamageFallof));
					
					FDamageInfo DamageInfo;
					DamageInfo.Amount = DamageCalc;
					DamageInfo.DamageCauser = GetInstigator();

					Damageable->TakeDamage(DamageInfo);

					DamagedActors.Add(HitResult.GetActor());
				}
			
			}
		}
	}
	Destroy();
}

void AVoidProjectile::Destroyed()
{
	Super::Destroyed();
	
	if (ImpactSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
	}
	if (ImpactParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactParticle, GetActorLocation());
	}
}

void AVoidProjectile::SpawnTrailSystem()
{
	if (TrailSystem)
	{
		TrailSystemComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(TrailSystem, GetRootComponent(),
			FName(), GetActorLocation(), GetActorRotation(),
			EAttachLocation::Type::KeepWorldPosition, false);
	}
}

void AVoidProjectile::StartDestroyTimer()
{
	GetWorld()->GetTimerManager().SetTimer(DestroyTimer,
		this,
		&AVoidProjectile::DestroyTimerFinished,
		DestroyTime);
}

void AVoidProjectile::DestroyTimerFinished()
{
	Destroy();
}



