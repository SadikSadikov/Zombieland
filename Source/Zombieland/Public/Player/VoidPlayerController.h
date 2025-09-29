// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VoidPlayerController.generated.h"

class AVoidHUD;
/**
 * 
 */
UCLASS()
class ZOMBIELAND_API AVoidPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	void SetHUDHealth(float Health, float MaxHealth);


protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY()
	AVoidHUD* VoidHUD;
	
};
