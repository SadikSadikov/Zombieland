// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Projectile/VoidProjectile.h"

#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


AVoidProjectile::AVoidProjectile()
{

	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(BoxComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));

}

void AVoidProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVoidProjectile::OnHit()
{
	Destroy();
}

