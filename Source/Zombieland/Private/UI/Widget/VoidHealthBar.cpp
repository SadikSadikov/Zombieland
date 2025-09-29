// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/VoidHealthBar.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UVoidHealthBar::SetHealthBarPercentage(const float Percentage)
{
	HealthBar->SetPercent(Percentage);
}

void UVoidHealthBar::SetHealthText(const FString& Text)
{
	HealthText->SetText(FText::FromString(Text));
}
