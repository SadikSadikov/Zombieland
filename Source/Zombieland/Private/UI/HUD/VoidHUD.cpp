// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/VoidHUD.h"
#include "UI/Widget/VoidUserWidget.h"
#include "Blueprint/UserWidget.h"

void AVoidHUD::InitOverlay()
{
	if (VoidOverlayWidgetClass == nullptr) return;
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), VoidOverlayWidgetClass);
	VoidOverlayWidget = Cast<UVoidUserWidget>(Widget);

	Widget->AddToViewport();
}
