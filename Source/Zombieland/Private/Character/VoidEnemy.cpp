// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/VoidEnemy.h"

#include "AI/VoidAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Component/CombatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AActor* AVoidEnemy::GetCombatTarget_Implementation()
{
	return CombatTarget;
}

void AVoidEnemy::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
	HitTarget = CombatTarget->GetActorLocation();
}

void AVoidEnemy::Attack_Implementation()
{
	CombatComp->Attack(EAttackType::EAT_Primary);
}

AVoidEnemy::AVoidEnemy()
{
	Tags.Add(TEXT("Enemy"));
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
}

void AVoidEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (BehaviorTree)
	{
		if (AVoidAIController* VoidAIController = Cast<AVoidAIController>(NewController))
		{
			VoidAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
			VoidAIController->RunBehaviorTree(BehaviorTree);
			
		}
		
	}
	
}
