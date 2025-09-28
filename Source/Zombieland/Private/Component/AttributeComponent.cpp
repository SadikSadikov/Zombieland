// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/AttributeComponent.h"

UAttributeComponent::UAttributeComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;
	
}


void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void UAttributeComponent::Heal(float Amount)
{
	Health = FMath::Clamp(Health + Amount, 0, MaxHealth);
}

void UAttributeComponent::TakeDamage(const FDamageInfo& DamageInfo)
{
	if (bIsDead) return;
	
	Health = FMath::Clamp(Health - DamageInfo.Amount, 0.f, MaxHealth);
	
	OnDamageTaken.Broadcast(DamageInfo);


	if (Health == 0.f)
	{
		bIsDead = true;
		OnDeath.Broadcast();
		
	}
	
}

