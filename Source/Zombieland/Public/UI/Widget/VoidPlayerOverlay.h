// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/VoidUserWidget.h"
#include "VoidPlayerOverlay.generated.h"


class UVoidHealthBar;
/**
 * 
 */
UCLASS()
class ZOMBIELAND_API UVoidPlayerOverlay : public UVoidUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVoidHealthBar> HealthBar;


	
};
