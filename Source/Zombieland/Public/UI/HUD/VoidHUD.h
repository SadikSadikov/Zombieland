// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "VoidHUD.generated.h"

class UVoidPlayerOverlay;
/**
 * 
 */
UCLASS()
class ZOMBIELAND_API AVoidHUD : public AHUD
{
	GENERATED_BODY()

public:

	void InitOverlay();

	UPROPERTY()
	TObjectPtr<UVoidPlayerOverlay> VoidOverlayWidget;

protected:

private:

	UPROPERTY(EditAnywhere, Category = "Properties")
	TSubclassOf<UVoidPlayerOverlay> VoidOverlayWidgetClass;

	
	
};
