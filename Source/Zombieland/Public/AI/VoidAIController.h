// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "VoidAIController.generated.h"

class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class ZOMBIELAND_API AVoidAIController : public AAIController
{
	GENERATED_BODY()

public:

	AVoidAIController();

private:

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

public:

	FORCEINLINE UBehaviorTreeComponent* GetBehaviorTreeComponent() { return BehaviorTreeComponent; }
	
};
