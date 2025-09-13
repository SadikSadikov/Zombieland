// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/VoidCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/VoidPlayerController.h"

void AVoidCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(VoidContext, 0);
		}
	}
}

void AVoidCharacter::PollInit()
{
	
	if (VoidPlayerController == nullptr)
	{
		/*VoidPlayerController = VoidPlayerController == nullptr ? Cast<AVoidPlayerController>(GetController()) : VoidPlayerController;
		if (VoidPlayerController)
		{
			// HUD Releated thinsgs
		}*/
	}
	
}


AVoidCharacter::AVoidCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AVoidCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AVoidCharacter::Move);
	}
}

void AVoidCharacter::CalcActorRotation(float DeltaTime)
{
	const FRotator ActorRotation = GetActorRotation();
	
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	FHitResult Hit;
	PlayerController->GetHitResultUnderCursorByChannel(TraceTypeQuery1, false, Hit);

	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Hit.Location);

	FRotator CursorRotation = FMath::RInterpTo(GetActorRotation(), LookAtRotation, DeltaTime, 6.0f);
	
	SetActorRotation(FRotator(ActorRotation.Pitch, CursorRotation.Yaw, ActorRotation.Roll));
}

float AVoidCharacter::CalcSpeed()
{
	FVector CharVelocity = GetCharacterMovement()->Velocity;
	CharVelocity.Z = 0;
	return CharVelocity.Size();
}

void AVoidCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CalcActorRotation(DeltaTime);

	float Speed = CalcSpeed();

	if (Speed == 0.f)
	{
		
		FRotator CurrentRotation = FRotator(0.f, GetActorRotation().Yaw, 0.f);
		/* [180 / -180] */
		FRotator DeltaRotation = UKismetMathLibrary::NormalizedDeltaRotator(CurrentRotation, StartingRotator);
		PrevYaw_Rot = Yaw_Rot;
		Yaw_Rot = DeltaRotation.Yaw;
	
		if (TurningInPlace == ETurningInPlace::ETIP_NotTurning)
		{
			InterpYaw_Rot = Yaw_Rot;
		}
		
		TurnInPlace(DeltaTime);
	}
	else if (Speed > 0.f)
	{
		StartingRotator = FRotator(0.f, GetActorRotation().Yaw, 0.f);
		Yaw_Rot = 0.f;
		TurningInPlace = ETurningInPlace::ETIP_NotTurning;
	}
	

}

void AVoidCharacter::TurnInPlace(float DeltaTime)
{
	if (Yaw_Rot > YawThreshold)
	{
		TurningInPlace = ETurningInPlace::ETIP_Right;
		
	}
	else if (Yaw_Rot < -YawThreshold)
	{
		TurningInPlace = ETurningInPlace::ETIP_Left;
		
	}

	// TODO:: If character not stopining to , then not change to idle anim keep in right direction for example
	if (TurningInPlace != ETurningInPlace::ETIP_NotTurning )
	{
		InterpYaw_Rot = FMath::FInterpTo(InterpYaw_Rot, 0.f, DeltaTime, 1.5f);
		Yaw_Rot = InterpYaw_Rot;
		
		

		if (FMath::Abs(Yaw_Rot) < YawMinThreshold)
		{
			TurningInPlace = ETurningInPlace::ETIP_NotTurning;
			StartingRotator = FRotator(0.f, GetActorRotation().Yaw, 0.f);
		}
		
	}
}

void AVoidCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D InputAxisVector = Value.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, InputAxisVector.Y);
	AddMovementInput(RightDirection, InputAxisVector.X);
}
