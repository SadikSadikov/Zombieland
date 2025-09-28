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

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AVoidProjectile::OnHit);
	
}

void AVoidProjectile::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetInstigator()) return;

	if (IDamageableInterface* Damageable = Cast<IDamageableInterface>(OtherActor))
	{
		if (IWeaponInterface* WeaponInterface = Cast<IWeaponInterface>(GetOwner()))
		{
			
			FDamageInfo DamageInfo;
			DamageInfo.Amount = WeaponInterface->GetDamage();
			DamageInfo.DamageCauser = OtherActor;
			
			Damageable->TakeDamage(DamageInfo);
		}
		
	}

	OtherActorTag = OtherActor->ActorHasTag(FName("Player")) || OtherActor->ActorHasTag(FName("Enemy")) ? FName("Character") : FName("Environment");
	
	Destroy();
}

void AVoidProjectile::Destroyed()
{
	Super::Destroyed();

	//TODO:: Make choicer for other actor if is Character make impact sound and effect for character , for Environment same and for other types etc.... 
	
	if (ImpactCharacter && OtherActorTag == FName("Character"))
	{
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactCharacterParticle, GetActorTransform());
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactCharacter, GetActorLocation());
	}
	else if (ImpactEnvironmentParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEnvironmentParticle, GetActorTransform());
	}
	
	if (ImpactSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
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



