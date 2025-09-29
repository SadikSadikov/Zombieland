// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "VoidHUD.generated.h"

class UVoidUserWidget;
/**
 * 
 */
UCLASS()
class ZOMBIELAND_API AVoidHUD : public AHUD
{
	GENERATED_BODY()

public:

	void InitOverlay();

protected:

private:

	UPROPERTY()
	TObjectPtr<UVoidUserWidget> VoidOverlayWidget;

	UPROPERTY(EditAnywhere, Category = "Properties")
	TSubclassOf<UVoidUserWidget> VoidOverlayWidgetClass;

	
	
};
