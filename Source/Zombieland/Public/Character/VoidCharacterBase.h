// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VoidTypes/WeaponTypes.h"
#include "VoidCharacterBase.generated.h"

class UCombatComponent;

UCLASS()
class ZOMBIELAND_API AVoidCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	
	AVoidCharacterBase();

	virtual  void PostInitializeComponents() override;

	void PlayAttackMontage(const EWeaponType WeaponType);

	void PlayRechargeMontage();
	

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Combat|Animation")
	TMap<EWeaponType, UAnimMontage*> WeaponMontages;

	UPROPERTY(EditDefaultsOnly, Category = "Combat|Animation")
	TObjectPtr<UAnimMontage> RechargeMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCombatComponent* CombatComp;

	FVector HitTarget = FVector::ZeroVector;

public:

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UCombatComponent* GetCombatComponent() const { return CombatComp; }
	FORCEINLINE const FVector& GetHitTarget() const { return HitTarget; }
	
	

};
