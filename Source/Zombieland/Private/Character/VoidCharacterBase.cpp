// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/VoidCharacterBase.h"

#include "Component/CombatComponent.h"


AVoidCharacterBase::AVoidCharacterBase()
{

	PrimaryActorTick.bCanEverTick = true;

	CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat"));

}

void AVoidCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (CombatComp)
	{
		CombatComp->SetCharacterOwner(this);
	}
}

void AVoidCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}



