// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/VoidCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "VoidEnemy.generated.h"

class UBehaviorTree;
/**
 * 
 */
UCLASS()
class ZOMBIELAND_API AVoidEnemy : public AVoidCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:

	/* Enemy Interface */
	virtual AActor* GetCombatTarget_Implementation() override;

	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;

	virtual void Attack_Implementation() override;
	
	/* end Enemy Interface */

	AVoidEnemy();

	virtual void PossessedBy(AController* NewController) override;

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	TObjectPtr<AActor> CombatTarget;

private:
	
	UPROPERTY(EditAnywhere, Category = "Comabt|AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
};


