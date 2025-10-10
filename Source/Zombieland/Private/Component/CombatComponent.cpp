// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/CombatComponent.h"

#include "Character/VoidCharacterBase.h"
#include "Engine/SkeletalMeshSocket.h"


UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	if (CharacterOwner)
	{
		CharacterOwner->OnMontageIsInterruptedDelegate.AddUniqueDynamic(this, &UCombatComponent::MontageIsInterrupted);
	}

	SpawnDefaultWeapon();

	CombatState = ECombatState::ECS_Unoccupied;
	OnCombatStateChangedDelegate.Broadcast(CombatState);
	
	
}

void UCombatComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCombatComponent::EquipWeapon(AVoidWeapon* WeaponToEquip)
{
	if (WeaponToEquip == nullptr) return;

	if (EquippedWeapon != nullptr && SecondaryWeapon == nullptr)
	{
		EquipSecondaryWeapon(WeaponToEquip);
	}
	else
	{
		EquipPrimaryWeapon(WeaponToEquip);
	}
		
}

void UCombatComponent::Attack(EAttackType AttackType)
{
	
	if (CharacterOwner && CanAttack())
	{
		if (CharacterOwner->Implements<UCombatInterface>())
		{
			ICombatInterface::Execute_UpdateFacingTarget(GetOwner(), CharacterOwner->GetHitTarget());
		}
		
		CombatState = ECombatState::ECS_Attacking;
		OnCombatStateChangedDelegate.Broadcast(CombatState);

		FName SectionName = FName("Default");
		if (EquippedWeapon->IsCanCombo())
		{
			
			SectionName = FName(*FString::Printf(TEXT("Attack%d"),CurrentComboCount));
			
			CurrentComboCount++;
			
		}

		CurrentAttackType = AttackType;
		CharacterOwner->DisableMovement(true);
		CharacterOwner->PlayAttackMontage(EquippedWeapon->GetWeaponType(),CurrentMontageLength, AttackType, SectionName);
		StartAttackTimer(CurrentMontageLength);
		
	}
}

bool UCombatComponent::CanAttack()
{
	if (EquippedWeapon == nullptr) return false;

	
	return EquippedWeapon->CanAttack() && CombatState == ECombatState::ECS_Unoccupied;
}

void UCombatComponent::AttackImpact()
{
	if (CurrentAttackType == EAttackType::EAT_Primary)
	{
		EquippedWeapon->PrimaryAttack(CharacterOwner->GetHitTarget());
	}
	else if (CurrentAttackType == EAttackType::EAT_Secondary)
	{
		EquippedWeapon->SecondaryAttack(CharacterOwner->GetHitTarget());
	}

	CharacterOwner->DisableMovement(false);
	

}

void UCombatComponent::StartAttackTimer(float MontageLength)
{
	if (CharacterOwner == nullptr || EquippedWeapon == nullptr) return;

	CharacterOwner->GetWorldTimerManager().SetTimer(AttackTimer,
		this,
		&UCombatComponent::AttackTimerFinished,
		MontageLength + EquippedWeapon->GetAttackDelay(CurrentAttackType));


	if (EquippedWeapon->IsCanCombo())
	{
		StratComboTimer(MontageLength);
	}
	
}

void UCombatComponent::StratComboTimer(float MontageLength)
{
	if (CharacterOwner == nullptr || EquippedWeapon == nullptr) return;
	
	CharacterOwner->GetWorldTimerManager().SetTimer(ComboTimer,
		this,
		&UCombatComponent::ComboTimerFinished,
		MontageLength+ EquippedWeapon->GetAttackDelay(CurrentAttackType) + FMath::Abs(EquippedWeapon->GetComboTimer()));
}

void UCombatComponent::AttackTimerFinished()
{
	if (EquippedWeapon == nullptr) return;

	if (EquippedWeapon->IsCanCombo() && CurrentComboCount > EquippedWeapon->GetComboCount())
	{
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([this]()
		{
			ComboTimerFinished();
			ClearAttackData();
		
		}), EquippedWeapon->GetAttackDelay(CurrentAttackType) / 2.f, false);
	}
	else
	{
		ClearAttackData();
	}
	
	
	
}

void UCombatComponent::ClearAttackData()
{
	CurrentMontageLength = 0.f;
	CombatState = ECombatState::ECS_Unoccupied;
	OnCombatStateChangedDelegate.Broadcast(CombatState);
	RechargeEmptyWeapon();
}


void UCombatComponent::ComboTimerFinished()
{
	if (EquippedWeapon == nullptr) return;

	CurrentComboCount = 1;


	
}

void UCombatComponent::RechargeEmptyWeapon()
{
	if (EquippedWeapon && !EquippedWeapon->CanAttack())
	{
		Recharge();
	}
}

void UCombatComponent::Recharge()
{
	if (CanRecharge())
	{
		CombatState = ECombatState::ECS_Recharging;
		OnCombatStateChangedDelegate.Broadcast(CombatState);
		CharacterOwner->PlayRechargeMontage();
	}
}

bool UCombatComponent::CanSwap()
{
	bool bCheckValid = CharacterOwner &&
		EquippedWeapon &&
			SecondaryWeapon &&
				CombatState == ECombatState::ECS_Unoccupied;
	
	return bCheckValid;
}

void UCombatComponent::SwapWeapon()
{
	if (CanSwap())
	{
		CombatState = ECombatState::ECS_SwappingWeapons;
		OnCombatStateChangedDelegate.Broadcast(CombatState);
		CharacterOwner->PlaySwapWeaponMontage();
	}
	
}

void UCombatComponent::SwapWeaponFinished()
{
	
	CombatState = ECombatState::ECS_Unoccupied;
	OnCombatStateChangedDelegate.Broadcast(CombatState);
	RechargeEmptyWeapon();
	
}

void UCombatComponent::SwapBegin()
{
	AVoidWeapon* TempWeapon = EquippedWeapon;
	EquippedWeapon = SecondaryWeapon;
	SecondaryWeapon = TempWeapon;

	AttachWeaponToRightHand(EquippedWeapon);
	AttachWeaponToBackpack(SecondaryWeapon);
	
}

void UCombatComponent::RechargeFinished()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->Recharge();
	}
	CombatState = ECombatState::ECS_Unoccupied;
	OnCombatStateChangedDelegate.Broadcast(CombatState);
}

bool UCombatComponent::CanRecharge()
{
	return EquippedWeapon && EquippedWeapon->CanRecharge() && CombatState == ECombatState::ECS_Unoccupied;
}

void UCombatComponent::EquipPrimaryWeapon(AVoidWeapon* WeaponToEquip)
{
	EquippedWeapon = WeaponToEquip;
	EquippedWeapon->SetOwner(GetOwner());
	EquippedWeapon->SetInstigator(Cast<APawn>(GetOwner()));
	AttachWeaponToRightHand(EquippedWeapon);
	
}

void UCombatComponent::EquipSecondaryWeapon(AVoidWeapon* WeaponToEquip)
{
	SecondaryWeapon = WeaponToEquip;
	SecondaryWeapon->SetOwner(GetOwner());
	SecondaryWeapon->SetInstigator(Cast<APawn>(GetOwner()));
	AttachWeaponToBackpack(SecondaryWeapon);
}

void UCombatComponent::AttachWeaponToRightHand(AActor* WeaponToAttach)
{
	if (CharacterOwner == nullptr || CharacterOwner->GetMesh() == nullptr || WeaponToAttach == nullptr ) return;

	// TODO:: Change this later
	FName SocketName = FName("RightHandSocket");
	if (EquippedWeapon->GetWeaponType() == EWeaponType::EWT_Gun)
	{
		SocketName = FName("RightHandGunSocket");
	}
	else if (EquippedWeapon->GetWeaponType() == EWeaponType::EWT_Sword)
	{
		SocketName = FName("RightHandSwordSocket");
	}
	
	if (const USkeletalMeshSocket* MeshSocket = CharacterOwner->GetMesh()->GetSocketByName(SocketName))
	{
		MeshSocket->AttachActor(WeaponToAttach, CharacterOwner->GetMesh());
	}
}

void UCombatComponent::AttachWeaponToBackpack(AActor* WeaponToAttach)
{
	if (CharacterOwner == nullptr || CharacterOwner->GetMesh() == nullptr || WeaponToAttach == nullptr ) return;

	// TODO:: Change this later
	FName SocketName = FName("BackpackSocket");
	if (SecondaryWeapon->GetWeaponType() == EWeaponType::EWT_Gun)
	{
		SocketName = FName("BackpackGunSocket");
	}
	else if (SecondaryWeapon->GetWeaponType() == EWeaponType::EWT_Sword)
	{
		SocketName = FName("BackpackSwordSocket");
	}
	
	if (const USkeletalMeshSocket* MeshSocket = CharacterOwner->GetMesh()->GetSocketByName(SocketName))
	{
		MeshSocket->AttachActor(WeaponToAttach, CharacterOwner->GetMesh());
	}
}

void UCombatComponent::SpawnDefaultWeapon()
{

	if (GetWorld() && DefaultWeaponClass)
	{
		if (AVoidWeapon* Weapon = GetWorld()->SpawnActor<AVoidWeapon>(DefaultWeaponClass))
		{
			EquipWeapon(Weapon);
		}
	
	}

	if (GetWorld() && SecondaryWeaponClass)
	{
		if (AVoidWeapon* Weapon = GetWorld()->SpawnActor<AVoidWeapon>(SecondaryWeaponClass))
		{
			EquipSecondaryWeapon(Weapon);
		}
	}
}

void UCombatComponent::MontageIsInterrupted(ECombatState CurrentCombatState)
{
	if (CurrentCombatState == ECombatState::ECS_Attacking)
	{
		StartAttackTimer(CurrentMontageLength);
		CharacterOwner->DisableMovement(false);
	}
	else if (CurrentCombatState == ECombatState::ECS_Recharging)
	{
		RechargeFinished();
	}
	else if (CurrentCombatState == ECombatState::ECS_SwappingWeapons)
	{
		SwapWeaponFinished();
	}
	
}

EWeaponType UCombatComponent::GetEquippedWeaponType() const
{
	if (EquippedWeapon)
	{
		return EquippedWeapon->GetWeaponType();
	}

	return EWeaponType::EWT_Max;
}


