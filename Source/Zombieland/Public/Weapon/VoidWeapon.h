// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoidTypes/WeaponTypes.h"
#include "VoidWeapon.generated.h"



UENUM(BlueprintType)
enum class EAttackType  : uint8
{
	EAT_Primary UMETA(DisplayName = "Primary"),
	EAT_Secondary UMETA(DisplayName = "Secondary"),

	EAT_Max UMETA(DisplayName = "DeafultMax")
	
};

UCLASS()
class ZOMBIELAND_API AVoidWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	
	AVoidWeapon();

	virtual void Attack(const FVector& TraceHitTarget);

	virtual void Recharge();
	
	virtual bool CanAttack();

	virtual bool CanRecharge();

	


protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackDelay = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	EWeaponType WeaponType = EWeaponType::EWT_Unarmed;

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

public:

	FORCEINLINE EWeaponType GetWeaponType() const { return WeaponType; }
	FORCEINLINE UStaticMeshComponent* GetWeaponMesh() { return WeaponMesh; }
	FORCEINLINE float GetAttackDelay() const { return AttackDelay; }



	

};
