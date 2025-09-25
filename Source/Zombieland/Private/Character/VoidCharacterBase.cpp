// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/VoidCharacterBase.h"

#include "ViewportInteractionTypes.h"
#include "Component/AttributeComponent.h"
#include "Component/CombatComponent.h"
#include "Components/CapsuleComponent.h"


AVoidCharacterBase::AVoidCharacterBase()
{

	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	GetMesh()->SetCollisionObjectType(ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);

	
	CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat"));

	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attribute"));

	HitFlashTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("HitFlashTimeline"));

}



void AVoidCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	CreateHitFlashDynamicMaterial();
	

	if (AttributeComponent)
	{
		AttributeComponent->OnDamageTaken.AddDynamic(this, &AVoidCharacterBase::ReceiveDamage);

		AttributeComponent->OnDeath.AddDynamic(this, &AVoidCharacterBase::OnDeath);
	}
	
	
}

void AVoidCharacterBase::CreateHitFlashDynamicMaterial()
{
	if (bUseHitFlash && GetMesh())
	{
		for (UMaterialInterface* DyncMat : GetMesh()->GetMaterials())
		{
			UMaterialInstanceDynamic* TempMaterial = UMaterialInstanceDynamic::Create(DyncMat, this);
			HitFlashMaterials.Add(TempMaterial);
		}
		HitFlashTrack.BindDynamic(this, &AVoidCharacterBase::AVoidCharacterBase::UpdateEndHitFlash);
	}
}

float AVoidCharacterBase::GetHealth()
{
	if (AttributeComponent == nullptr) return -1.f;
	
	return AttributeComponent->GetHealth();
}

float AVoidCharacterBase::GetMaxHealth()
{
	if (AttributeComponent == nullptr)return -1.f;
	
	return AttributeComponent->GetMaxHealth();
}

void AVoidCharacterBase::Heal(float Amount)
{
	if (AttributeComponent == nullptr) return;
	
	AttributeComponent->Heal(Amount);
}

void AVoidCharacterBase::TakeDamage(const FDamageInfo& DamageInfo)
{
	if (AttributeComponent == nullptr) return;
	AttributeComponent->TakeDamage(DamageInfo);
}

void AVoidCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (CombatComp)
	{
		CombatComp->SetCharacterOwner(this);
	}
}

void AVoidCharacterBase::PlayAttackMontage(const EWeaponType WeaponType, EAttackType AttackType)
{
	
	if (WeaponMontages.IsEmpty() || !WeaponMontages.Contains(WeaponType)) return;

	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	{
		AnimInstance->Montage_Play(WeaponMontages[WeaponType]);
		const FName Section = AttackType == EAttackType::EAT_Primary ? FName("Primary") : FName("Secondary");
		
		AnimInstance->Montage_JumpToSection(Section, WeaponMontages[WeaponType]);
	}
}

void AVoidCharacterBase::PlayRechargeMontage()
{
	// TODO:: Choice which Weapon you want to charge
 	if (RechargeMontage)
	{
 		if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
 		{
 			AnimInstance->Montage_Play(RechargeMontage);
 		}
	}
}




void AVoidCharacterBase::ReceiveDamage()
{
	HitFlash();
}

void AVoidCharacterBase::OnDeath()
{
	// TODO:: Implement Die 
	GEngine->AddOnScreenDebugMessage(-1, 2.F, FColor::Red, TEXT("IsDead"));
}

void AVoidCharacterBase::HitFlash()
{
	if (bUseHitFlash && !HitFlashMaterials.IsEmpty())
	{
		int Counter = 0;
		for (UMaterialInstanceDynamic* DyncMat : HitFlashMaterials)
		{
			GetMesh()->SetMaterial(Counter, DyncMat);
			DyncMat->SetScalarParameterValue(FName("FlashMultiplier"), 1.f);
			DyncMat->SetVectorParameterValue(FName("FlashColor"), HitFlashColor);
			Counter++;
		}
		EndHitFlash();

		
	}
}

void AVoidCharacterBase::EndHitFlash()
{
	if (HitFlashCurve && HitFlashTimeline)
	{
		HitFlashTimeline->AddInterpFloat(HitFlashCurve, HitFlashTrack);
		HitFlashTimeline->SetPlayRate(HitFlashPlayRate);
		HitFlashTimeline->PlayFromStart();
	}
}

void AVoidCharacterBase::UpdateEndHitFlash(float HitFlashValue)
{
	for (UMaterialInstanceDynamic* DyncMat : HitFlashMaterials)
	{
		DyncMat->SetScalarParameterValue(FName("FlashMultiplier"), HitFlashValue);
	}
}





