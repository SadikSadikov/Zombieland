// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/WeaponInterface.h"
#include "VoidTypes/WeaponTypes.h"
#include "VoidWeapon.generated.h"

UCLASS()
class ZOMBIELAND_API AVoidWeapon : public AActor, public IWeaponInterface
{
	GENERATED_BODY()
	
public:
	
	AVoidWeapon();

	/* Weapon Interface */

	virtual float GetDamage() override;

	/* end Weapon Interface */

	virtual void PrimaryAttack(const FVector& TraceHitTarget);

	virtual void SecondaryAttack(const FVector& TraceHitTarget);

	virtual void Recharge();
	
	virtual bool CanAttack();

	virtual bool CanRecharge();

	


protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackDelay = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	EWeaponType WeaponType = EWeaponType::EWT_Unarmed;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float Damage = 5.f;

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

	

public:

	FORCEINLINE EWeaponType GetWeaponType() const { return WeaponType; }
	FORCEINLINE UStaticMeshComponent* GetWeaponMesh() { return WeaponMesh; }
	FORCEINLINE float GetAttackDelay() const { return AttackDelay; }



	

};
