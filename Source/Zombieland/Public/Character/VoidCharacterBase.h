// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "Interaction/DamageableInterface.h"
#include "VoidTypes/WeaponTypes.h"
#include "VoidCharacterBase.generated.h"
class UAttributeComponent;
class UCombatComponent;

UCLASS()
class ZOMBIELAND_API AVoidCharacterBase : public ACharacter, public IDamageableInterface, public ICombatInterface
{
	GENERATED_BODY()

public:

	
	
	AVoidCharacterBase();
	void CreateHitFlashDynamicMaterial();

	/* Damageable Interface*/

	virtual float GetHealth() override;

	virtual float GetMaxHealth() override;

	virtual void Heal(float Amount) override;

	virtual void TakeDamage(const FDamageInfo& DamageInfo) override;

	/* end Damageable Interface*/

	virtual  void PostInitializeComponents() override;

	void PlayAttackMontage(const EWeaponType WeaponType, EAttackType AttackType);

	void PlayRechargeMontage();
	void HitFlash();

protected:
	
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void ReceiveDamage();

	UFUNCTION()
	virtual void OnDeath();

	UPROPERTY(EditDefaultsOnly, Category = "Combat|Animation")
	TMap<EWeaponType, UAnimMontage*> WeaponMontages;

	UPROPERTY(EditDefaultsOnly, Category = "Combat|Animation")
	TObjectPtr<UAnimMontage> RechargeMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCombatComponent* CombatComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAttributeComponent* AttributeComponent;

	FVector HitTarget = FVector::ZeroVector;

	// Hit Flash

	UPROPERTY(EditAnywhere, Category = "Combat|HitFlash")
	bool bUseHitFlash = true;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTimelineComponent> HitFlashTimeline;

	FOnTimelineFloat HitFlashTrack;

	UPROPERTY(EditAnywhere, Category = "Combat|HitFlash")
	TObjectPtr<UCurveFloat> HitFlashCurve;

	UPROPERTY()
	TArray<UMaterialInstanceDynamic*> HitFlashMaterials;

	UPROPERTY(EditAnywhere, Category = "Combat|HitFlash")
	FLinearColor HitFlashColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, Category = "Combat|HitFlash")
	float HitFlashPlayRate = 5.f;

private:

	void EndHitFlash();

	UFUNCTION()
	void UpdateEndHitFlash(float HitFlashValue);

public:

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UCombatComponent* GetCombatComponent() const { return CombatComp; }
	FORCEINLINE const FVector& GetHitTarget() const { return HitTarget; }
	
	

};
