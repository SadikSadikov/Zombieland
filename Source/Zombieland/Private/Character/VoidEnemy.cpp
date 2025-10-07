// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/VoidEnemy.h"

#include "AI/VoidAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Component/CombatComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/Widget/VoidHealthBar.h"

AVoidEnemy::AVoidEnemy()
{
	Tags.Add(TEXT("Enemy"));
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->MaxWalkSpeed = 400.f;

	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthBar->SetupAttachment(GetRootComponent());
	
}

void AVoidEnemy::BeginPlay()
{
	Super::BeginPlay();

	UpdateHealthBar();
	
}

void AVoidEnemy::UpdateHealthBar()
{
	if (HealthBar)
	{
		if (UVoidHealthBar* ProgressBar = Cast<UVoidHealthBar>(HealthBar->GetUserWidgetObject()))
		{
			ProgressBar->SetHealthBarPercentage(GetHealth() / GetMaxHealth());

			const FString HealthText = FString::Printf(TEXT("%d/%d"), FMath::CeilToInt(GetHealth()), FMath::CeilToInt(GetMaxHealth()));
			ProgressBar->SetHealthText(HealthText);
		}
	}
}



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



void AVoidEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (BehaviorTree)
	{
		VoidAIController = Cast<AVoidAIController>(NewController);
		if (VoidAIController)
		{
			VoidAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		
			VoidAIController->RunBehaviorTree(BehaviorTree);
			VoidAIController->GetBlackboardComponent()->SetValueAsBool(FName("IsDead"), IsDead());
			VoidAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), IsHitReacting());
			
			
		}
		
	}
	
}

void AVoidEnemy::ReceiveDamage(const FDamageInfo& DamageType)
{
	Super::ReceiveDamage(DamageType);

	if (HealthBar)
	{
		if (UVoidHealthBar* ProgressBar = Cast<UVoidHealthBar>(HealthBar->GetUserWidgetObject()))
		{
			ProgressBar->SetHealthBarPercentage(GetHealth() / GetMaxHealth());

			const FString HealthText = FString::Printf(TEXT("%d/%d"), FMath::CeilToInt(GetHealth()), FMath::CeilToInt(GetMaxHealth()));
			ProgressBar->SetHealthText(HealthText);
		}
	}
	
	
}

void AVoidEnemy::OnDeath()
{

	Super::OnDeath();
	
	SetLifeSpan(LifeSpan);

	if (VoidAIController)
	{
		VoidAIController->GetBlackboardComponent()->SetValueAsBool(FName("IsDead"), IsDead());
	}
	
	
	
}

void AVoidEnemy::PlayHitReactMontage()
{
	Super::PlayHitReactMontage();
	
	GetCharacterMovement()->MaxWalkSpeed = 0.f;
	if (VoidAIController)
	{
		VoidAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), IsHitReacting());
	}
}

void AVoidEnemy::OnCombatStateChanged(ECombatState NewState)
{
	if (VoidAIController)
	{
		VoidAIController->GetBlackboardComponent()->SetValueAsEnum(FName("CombatState"), static_cast<uint8>(NewState));
	}
}

void AVoidEnemy::EndHitReacting()
{
	Super::EndHitReacting();
	
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	if (VoidAIController)
	{
		VoidAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), IsHitReacting());
	}
}


