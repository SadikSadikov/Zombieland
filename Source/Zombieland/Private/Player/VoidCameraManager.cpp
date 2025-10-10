// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/VoidCameraManager.h"
#include "Kismet/KismetMathLibrary.h"

AVoidCameraManager::AVoidCameraManager()
{
	bIsOrthographic = true;
	DefaultOrthoWidth = 3000.f;
}

void AVoidCameraManager::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void AVoidCameraManager::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
	Super::UpdateViewTarget(OutVT, DeltaTime);
	
	FVector ActorLocation = OutVT.Target->GetActorLocation();

	FVector CalcLocation = ActorLocation + CameraLocOffset;
	OutVT.POV.Location = CalcLocation;
	OutVT.POV.Rotation = UKismetMathLibrary::FindLookAtRotation(CalcLocation, ActorLocation);

	
}
