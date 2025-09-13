// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animation/VoidAnimInstance.h"

#include "KismetAnimationLibrary.h"
#include "Character/VoidCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UVoidAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	VoidPlayer = Cast<AVoidCharacter>(TryGetPawnOwner());
	if (VoidPlayer)
	{
		VoidMovementComponent = VoidPlayer->GetCharacterMovement();
	}
	
}

void UVoidAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (VoidPlayer == nullptr)
	{
		VoidPlayer = Cast<AVoidCharacter>(TryGetPawnOwner());
	}
	if (VoidPlayer == nullptr) return;
	
	if (VoidMovementComponent == nullptr)
	{
		VoidMovementComponent = VoidPlayer->GetCharacterMovement();
		
	}
	if (VoidMovementComponent == nullptr) return;

	FVector Velocity = VoidMovementComponent->Velocity;
	Velocity.Z = 0.0f;
	Speed = Velocity.Size();

	Direction = UKismetAnimationLibrary::CalculateDirection(Velocity, VoidPlayer->GetActorRotation());

	TurningInPlace = VoidPlayer->GetTurningInPlace();
}
