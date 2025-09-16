// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VoidTypes/CombatState.h"
#include "Weapon/VoidWeapon.h"
#include "CombatComponent.generated.h"

class AVoidCharacterBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZOMBIELAND_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UCombatComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(AVoidWeapon* WeaponToEquip);

	/* This function is called in AnimNotify to Spawn a Projectile or Field for Collision */
	UFUNCTION(BlueprintCallable)
	void AttackImpact(EAttackType AttackType);

	/* This function is called in AnimNotify to Reload Gun or Recharge Sword */
	UFUNCTION(BlueprintCallable)
	void RechargeFinished();

	UFUNCTION(BlueprintCallable)
	void Attack(EAttackType AttackType);

	UFUNCTION(BlueprintCallable)
	void Recharge();
	

protected:

	virtual void BeginPlay() override;

	// Attack

	void FireGun();

	bool CanAttack();

	void StartAttackTimer();

	void AttackTimerFinished();

	FTimerHandle AttackTimer;

	// Recharge
	
	bool CanRecharge();

	void RechargeEmptyWeapon();
	
	//

	UPROPERTY()
	TObjectPtr<AVoidWeapon> EquippedWeapon;

	UPROPERTY()
	TObjectPtr<AVoidWeapon> SecondaryWeapon;
	

private:

	UPROPERTY()
	TObjectPtr<AVoidCharacterBase> CharacterOwner;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AVoidWeapon> DefaultWeaponClass;

	FVector HitTarget = FVector::ZeroVector;

	ECombatState CombatState = ECombatState::ECS_Unoccupied;

	void EquipPrimaryWeapon(AVoidWeapon* WeaponToEquip);

	void EquipSecondaryWeapon(AVoidWeapon* WeaponToEquip);

	void AttachWeaponToRightHand(AActor* WeaponToAttach);

	void SpawnDefaultWeapon();

	
public:

	FORCEINLINE AVoidCharacterBase* GetCharacterOwner() { return CharacterOwner; }
	FORCEINLINE void SetCharacterOwner(AVoidCharacterBase* InCharacterOwner) { CharacterOwner = InCharacterOwner; }



		
};




