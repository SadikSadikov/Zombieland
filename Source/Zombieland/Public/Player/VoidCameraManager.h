// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "VoidCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIELAND_API AVoidCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	
	AVoidCameraManager();

protected:

	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Camera Properties")
	FVector CameraLocOffset = FVector(-1200.f, 0.f, 1200);
	
};
