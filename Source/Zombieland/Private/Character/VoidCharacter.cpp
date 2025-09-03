// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/VoidCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

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

void AVoidCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	const FRotator ActorRotation = GetActorRotation();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	FHitResult Hit;
	PlayerController->GetHitResultUnderCursorByChannel(TraceTypeQuery1, false, Hit);

	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Hit.Location);

	FRotator CursorRotation = FMath::RInterpTo(GetActorRotation(), LookAtRotation, DeltaTime, 6.0f);
	
	SetActorRotation(FRotator(ActorRotation.Pitch, CursorRotation.Yaw, ActorRotation.Roll));
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
