// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/VoidWeapon.h"
#include "VoidMeleeWeapon.generated.h"

class UBoxComponent;
/**
 * 
 */
UCLASS()
class ZOMBIELAND_API AVoidMeleeWeapon : public AVoidWeapon
{
	GENERATED_BODY()

public:

	AVoidMeleeWeapon();
	
	void CreateSphereField(const FVector& TraceHitTarget, float Radius);

	virtual void PrimaryAttack(const FVector& TraceHitTarget) override;

	virtual void SecondaryAttack(const FVector& TraceHitTarget) override;
	
	virtual bool CanAttack() override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float PrimaryDamageRadius = 25.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float SecondaryDamageRadius = 50.f;

private:

	UPROPERTY(EditAnywhere, Category = "Combat|Effects")
	TObjectPtr<USoundBase> ImpactSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	bool bUseCameraShake = false;;

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (EditCondition = "bUseCameraShake"))
	TSubclassOf<UCameraShakeBase> CameraShakeClass;

	/* Take between 1% - 100% */
	UPROPERTY(EditAnywhere, Category = "Combat", meta = (EditCondition = "bUseCameraShake"))
	float CameraShakePercentage = 70.f;
	
	
};
