// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VoidCharacterBase.generated.h"

class UCombatComponent;

UCLASS()
class ZOMBIELAND_API AVoidCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	
	AVoidCharacterBase();

	virtual  void PostInitializeComponents() override;

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCombatComponent* CombatComp;
	
	

};
