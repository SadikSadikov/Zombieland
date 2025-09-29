// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/VoidHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widget/VoidPlayerOverlay.h"

void AVoidHUD::InitOverlay()
{
	if (VoidOverlayWidgetClass == nullptr) return;
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), VoidOverlayWidgetClass);
	VoidOverlayWidget = Cast<UVoidPlayerOverlay>(Widget);

	Widget->AddToViewport();
}
