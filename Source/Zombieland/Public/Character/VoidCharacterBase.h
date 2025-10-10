// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "Interaction/DamageableInterface.h"
#include "VoidTypes/CharacterClass.h"
#include "VoidTypes/CombatState.h"
#include "VoidTypes/WeaponTypes.h"
#include "VoidCharacterBase.generated.h"

class UNiagaraSystem;
class UAttributeComponent;
class UCombatComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMontageIsInterruptedSignature, ECombatState, CurrentCombatState);

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

	void PlayAttackMontage(const EWeaponType WeaponType, float& MontageLength,EAttackType InAttackType,  FName Section = FName("Default"));

	void PlayRechargeMontage();

	void PlaySwapWeaponMontage();

	// This function needs to be called in AnimNotify
	UFUNCTION(BlueprintCallable)
	virtual void EndHitReacting();

	FOnMontageIsInterruptedSignature OnMontageIsInterruptedDelegate;

	virtual void DisableMovement(bool bDisabled);

protected:
	
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void ReceiveDamage(const FDamageInfo& DamageType);

	UFUNCTION()
	virtual void OnDeath();

	void HitFlash();

	virtual void PlayHitReactMontage();

	virtual void InitActorInfo();

	UFUNCTION()
	virtual void OnCombatStateChanged(ECombatState NewState);

	UPROPERTY(EditDefaultsOnly, Category = "Combat|Animation")
	TMap<EWeaponType, FAttackState> WeaponMontages;

	UPROPERTY(EditDefaultsOnly, Category = "Combat|Animation")
	TObjectPtr<UAnimMontage> RechargeMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Combat|Animation")
	TObjectPtr<UAnimMontage> HitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Combat|Animation")
	TObjectPtr<UAnimMontage> SwapWeaponMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCombatComponent* CombatComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAttributeComponent* AttributeComponent;

	/* In Player HitTarget is Mouse Loc but in Enemy is Player Loc*/
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
	
	float BaseWalkSpeed = 0.f;



	// Death

	UPROPERTY(EditAnywhere, Category = "Combat|Death")
	FVector DeathImpulse;

	UPROPERTY(EditAnywhere)
	ECharacterClass CharacterClass = ECharacterClass::ECC_Warrior;

private:

	void EndHitFlash();

	UFUNCTION()
	void UpdateEndHitFlash(float HitFlashValue);

	UFUNCTION()
	void MontageIsInterrupted(UAnimMontage* Montage, bool bInterrupted);

	bool bHitReacting = false;

	bool bDead = false;

	UPROPERTY(EditAnywhere, Category = "Combat|Effect")
	TObjectPtr<UNiagaraSystem> ImpactCharacterEffect;

	UPROPERTY(EditAnywhere, Category = "Combat|Effects")
	TObjectPtr<USoundBase> ImpactCharacterSound;

public:

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UCombatComponent* GetCombatComponent() const { return CombatComp; }
	FORCEINLINE const FVector& GetHitTarget() const { return HitTarget; }
	FORCEINLINE bool IsHitReacting() const { return bHitReacting; }
	FORCEINLINE bool IsDead() const { return bDead; }

	
	

};
