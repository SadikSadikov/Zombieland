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

	virtual FDamageProps GetDamage() override;

	/* end Weapon Interface */

	virtual void PrimaryAttack(const FVector& TraceHitTarget);

	virtual void SecondaryAttack(const FVector& TraceHitTarget);

	virtual void Recharge();
	
	virtual bool CanAttack();

	virtual bool CanRecharge();

	


protected:
	
	virtual void BeginPlay() override;

	/* You need take into account the Montage Length*/
	UPROPERTY(EditAnywhere, Category = "Combat")
	float PrimaryAttackTimerDelay = 0.5f;

	/* You need take into account the Montage Length*/
	UPROPERTY(EditAnywhere, Category = "Combat")
	float SecondaryAttackTimerDelay = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	EWeaponType WeaponType = EWeaponType::EWT_Unarmed;

	/* If you enable bCanCombo you need to Add more Sequences into Montage and rename Sections like Attack1,2,3...  */
	UPROPERTY(EditAnywhere, Category = "Combat")
	bool bCanCombo = false;

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (EditCondition = "bCanCombo"))
	int32 ComboCount = 3;

	/* This value is used to add on top of AttackTimerDelay */
	UPROPERTY(EditAnywhere, Category = "Combat", meta = (EditCondition = "bCanCombo"))
	float ComboTimerDelay = 1.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	bool bUseTipSocket = false;
	
	UPROPERTY(EditAnywhere, Category = "Combat", meta = (EditCondition = "bUseTipSocket"))
	FName TipSocketName = FName("TipSocket");

	UPROPERTY(EditAnywhere, Category = "Combat")
	float Damage = 5.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bIsRadialDamage = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = bIsRadialDamage), Category = "Combat")
	float MinDamage = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = bIsRadialDamage), Category = "Combat")
	float InnerRadius = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = bIsRadialDamage), Category = "Combat")
	float OuterRadius = 0.f;

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

	

public:

	FORCEINLINE EWeaponType GetWeaponType() const { return WeaponType; }
	FORCEINLINE UStaticMeshComponent* GetWeaponMesh() { return WeaponMesh; }
	float GetAttackDelay(EAttackType InAttackType) const;
	FORCEINLINE bool IsCanCombo() const { return bCanCombo; }
	FORCEINLINE int32 GetComboCount() const { return ComboCount; }
	FORCEINLINE float GetComboTimer() const { return ComboTimerDelay; }



	

};
