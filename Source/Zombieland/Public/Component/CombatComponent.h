// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VoidTypes/CombatState.h"
#include "Weapon/VoidWeapon.h"
#include "CombatComponent.generated.h"

class AVoidCharacterBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCombatStateChangedSignature, ECombatState, NewState);

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
	void AttackImpact();

	/* This function is called in AnimNotify to Reload Gun or Recharge Sword */
	UFUNCTION(BlueprintCallable)
	void RechargeFinished();

	UFUNCTION(BlueprintCallable)
	void Attack(EAttackType AttackType);

	UFUNCTION(BlueprintCallable)
	void Recharge();
	bool CanSwap();

	UFUNCTION(BlueprintCallable)
	void SwapWeapon();

	/* This function is called in AnimNotify to Swap Weapon */
	UFUNCTION(BlueprintCallable)
	void SwapWeaponFinished();

	/* This function is called in AnimNotify to Swap Weapon */
	UFUNCTION(BlueprintCallable)
	void SwapBegin();

	UPROPERTY(BlueprintAssignable)
	FOnCombatStateChangedSignature OnCombatStateChangedDelegate;
	

protected:

	virtual void BeginPlay() override;

	// Attack

	bool CanAttack();

	void StartAttackTimer(float MontageLength);

	void StratComboTimer(float MontageLength);

	void AttackTimerFinished();

	void ComboTimerFinished();

	FTimerHandle AttackTimer;

	FTimerHandle ComboTimer;

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

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<AVoidWeapon> DefaultWeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<AVoidWeapon> SecondaryWeaponClass;

	FVector HitTarget = FVector::ZeroVector;

	ECombatState CombatState = ECombatState::ECS_Unoccupied;

	void EquipPrimaryWeapon(AVoidWeapon* WeaponToEquip);

	void EquipSecondaryWeapon(AVoidWeapon* WeaponToEquip);

	void AttachWeaponToRightHand(AActor* WeaponToAttach);

	void AttachWeaponToBackpack(AActor* WeaponToAttach);

	void SpawnDefaultWeapon();

	UFUNCTION()
	void MontageIsInterrupted(ECombatState CurrentCombatState);

	void ClearAttackData();
	
	int32 CurrentComboCount = 1;

	float CurrentMontageLength = 0.f;

	EAttackType CurrentAttackType = EAttackType::EAT_Primary;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	bool bShouldVisibleSecondaryWeapon = true;


	
public:

	FORCEINLINE ECombatState GetCombatState() const { return CombatState; }
	FORCEINLINE void SetCombatState(const ECombatState InCombatState) { CombatState = InCombatState; }
	FORCEINLINE AVoidCharacterBase* GetCharacterOwner() { return CharacterOwner; }
	FORCEINLINE void SetCharacterOwner(AVoidCharacterBase* InCharacterOwner) { CharacterOwner = InCharacterOwner; }
	EWeaponType GetEquippedWeaponType() const ;



		
};





