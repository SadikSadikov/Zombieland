// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoidWeapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponType  : uint8
{
	EWT_Unarmed UMETA(DisplayName = "Unarmed"),
	EWT_Sword UMETA(DisplayName = "Sword"),
	EWT_Gun UMETA(DisplayName = "Gun"),

	EWT_Max UMETA(DisplayName = "DeafultMax")
	
};

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

	virtual void Attack();

	UPROPERTY(EditAnywhere, Category = "Properties")
	EWeaponType WeaponType = EWeaponType::EWT_Unarmed;


protected:
	
	virtual void BeginPlay() override;

	

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

public:

	FORCEINLINE UStaticMeshComponent* GetWeaponMesh() { return WeaponMesh; }


	

};
