// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/VoidPlayerController.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "UI/HUD/VoidHUD.h"
#include "UI/Widget/VoidHealthBar.h"
#include "UI/Widget/VoidPlayerOverlay.h"


void AVoidPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(false);
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	SetInputMode(InputMode);

	
}

void AVoidPlayerController::SetHUDHealth(float Health, float MaxHealth)
{
	VoidHUD = VoidHUD == nullptr ? Cast<AVoidHUD>(GetHUD()) : VoidHUD;
	
	const bool bHUDValid = VoidHUD &&
		VoidHUD->VoidOverlayWidget &&
				VoidHUD->VoidOverlayWidget->HealthBar;

	if (bHUDValid)
	{
		const float HealthPercent = Health / MaxHealth;
		VoidHUD->VoidOverlayWidget->HealthBar->SetHealthBarPercentage(HealthPercent);
		const FString HealthText = FString::Printf(TEXT("%d/%d"), FMath::CeilToInt(Health), FMath::CeilToInt(MaxHealth));
		VoidHUD->VoidOverlayWidget->HealthBar->SetHealthText(HealthText);
	}
}
