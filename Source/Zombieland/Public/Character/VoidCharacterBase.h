// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VoidCharacterBase.generated.h"

UCLASS()
class ZOMBIELAND_API AVoidCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	
	AVoidCharacterBase();

protected:
	
	virtual void BeginPlay() override;
	
	

};
