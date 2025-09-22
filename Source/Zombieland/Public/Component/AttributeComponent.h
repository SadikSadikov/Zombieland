// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VoidTypes/DamageInfo.h"
#include "AttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDamageTaken);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZOMBIELAND_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UAttributeComponent();

	UPROPERTY(BlueprintAssignable)
	FOnDamageTaken OnDamageTaken;

	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;

	void Heal(float Amount);

	void TakeDamage(const FDamageInfo& DamageInfo);

protected:
	
	virtual void BeginPlay() override;



private:

	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	float Health = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	float MaxHealth = 100.f;

	// For now this is experimental
	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	float Speed = 600.f;

	bool bIsDead = false;

public:

	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }



		
};
