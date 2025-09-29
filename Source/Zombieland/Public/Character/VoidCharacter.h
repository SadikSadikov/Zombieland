// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/VoidCharacterBase.h"
#include "VoidTypes/TurningInPlace.h"
#include "VoidCharacter.generated.h"

class AVoidPlayerController;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;



UCLASS()
class ZOMBIELAND_API AVoidCharacter : public AVoidCharacterBase
{
	GENERATED_BODY()

public:

	AVoidCharacter();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;
	
	virtual void EndHitReacting() override;

	virtual void PossessedBy(AController* NewController) override;

protected:
	virtual void BeginPlay() override;

	virtual void ReceiveDamage(const FDamageInfo& DamageInfo) override;

	virtual void PlayHitReactMontage() override;
	
	virtual void InitActorInfo() override;

	// Poll for any relevant classes and initialize. Repeatedly check the status
	void PollInit();

private:

	// Animation

	ETurningInPlace TurningInPlace;

	FRotator StartingRotator;

	/* Rename more clearly*/

	UPROPERTY(EditDefaultsOnly);
	float InterpSpeedTurningInPlace = 1.5;
	
	UPROPERTY(EditDefaultsOnly);
	float YawThreshold = 5.f;

	UPROPERTY(EditDefaultsOnly);
	float YawMinThreshold = 2.f;

	bool bIsTurningInPlace = false;
	
	float Yaw_Rot;

	float PrevYaw_Rot;

	float InterpYaw_Rot;

	void TurnInPlace(float DeltaTime);

	void CalcActorRotation(float DeltaTime);
	
	float CalcSpeed() const;

	// end Animation

	bool CheckValidCombatInput() const;

	UPROPERTY()
	TObjectPtr<AVoidPlayerController> VoidPlayerController;

	// Input
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> VoidContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> FirstAttackAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> SecondAttackAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> RechargeAction;

	void Move(const FInputActionValue& Value);

	void FirstAttack(const FInputActionValue& Value);

	void SecondAttack(const FInputActionValue& Value);

	void Recharge(const FInputActionValue& Value);

	// end Input

public:

	FORCEINLINE ETurningInPlace GetTurningInPlace() const { return TurningInPlace; }
	
};
