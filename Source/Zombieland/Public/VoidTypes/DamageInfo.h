#pragma once

#include "CoreMinimal.h"
#include "DamageInfo.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FDamageInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Amount = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* DamageCauser = nullptr;
	
};

USTRUCT(Blueprintable, BlueprintType)
struct FDamageProps
{
	GENERATED_BODY()

	FDamageProps(){}

	FDamageProps(float BaseDamage, bool bIsRadialDamage, float MinDamage, float InnerRadius, float OuterRadius)
		: BaseDamage(BaseDamage),
		  bIsRadialDamage(bIsRadialDamage),
		  MinDamage(MinDamage),
		  InnerRadius(InnerRadius),
		  OuterRadius(OuterRadius)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseDamage = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsRadialDamage = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = bIsRadialDamage))
	float MinDamage = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = bIsRadialDamage))
	float InnerRadius = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = bIsRadialDamage))
	float OuterRadius = 0.f;
	
};