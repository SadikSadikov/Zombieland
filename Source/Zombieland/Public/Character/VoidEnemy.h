// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/VoidCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "VoidEnemy.generated.h"

class UWidgetComponent;
class AVoidAIController;
class UBehaviorTree;
/**
 * 
 */
UCLASS()
class ZOMBIELAND_API AVoidEnemy : public AVoidCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	
	AVoidEnemy();
	void UpdateHealthBar();

	/* Enemy Interface */
	virtual AActor* GetCombatTarget_Implementation() override;

	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;

	virtual void Attack_Implementation() override;
	
	/* end Enemy Interface */
	
	virtual void PossessedBy(AController* NewController) override;

	virtual void EndHitReacting() override;

	

protected:

	virtual void BeginPlay() override;

	virtual void ReceiveDamage(const FDamageInfo& DamageInfo) override;

	virtual void OnDeath() override;

	virtual void PlayHitReactMontage() override;

	virtual void OnCombatStateChanged(ECombatState NewState) override;

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	TObjectPtr<AActor> CombatTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	

private:

	

	UPROPERTY()
	AVoidAIController* VoidAIController;
	
	UPROPERTY(EditAnywhere, Category = "Comabt|AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	UPROPERTY(EditAnywhere, Category = "Comabt")
	float LifeSpan = 1.f;

	
	
};


