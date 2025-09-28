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