// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/VoidWeapon.h"
#include "CombatComponent.generated.h"

class AVoidCharacterBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZOMBIELAND_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UCombatComponent();

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(AVoidWeapon* WeaponToEquip);

	UFUNCTION(BlueprintCallable)
	void Attack(EAttackType AttackType);

protected:
	
	virtual void BeginPlay() override;

	void FireGun();

	UPROPERTY()
	TObjectPtr<AVoidWeapon> EquippedWeapon;

	UPROPERTY()
	TObjectPtr<AVoidWeapon> SecondaryWeapon;
	

private:

	UPROPERTY()
	TObjectPtr<AVoidCharacterBase> CharacterOwner;

	UPROPERTY(EditDefaultsOnly)
	TMap<EWeaponType, UAnimMontage*> WeaponMontages;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AVoidWeapon> DefaultWeaponClass;

	void EquipPrimaryWeapon(AVoidWeapon* WeaponToEquip);

	void EquipSecondaryWeapon(AVoidWeapon* WeaponToEquip);

	void AttachWeaponToRightHand(AActor* WeaponToAttach);

	void PlayAttackMontage(const EWeaponType WeaponType);

	void SpawnDefaultWeapon();

	
public:

	FORCEINLINE AVoidCharacterBase* GetCharacterOwner() { return CharacterOwner; }
	FORCEINLINE void SetCharacterOwner(AVoidCharacterBase* InCharacterOwner) { CharacterOwner = InCharacterOwner; }



		
};




