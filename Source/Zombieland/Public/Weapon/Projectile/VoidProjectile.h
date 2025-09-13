// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoidProjectile.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;

UCLASS()
class ZOMBIELAND_API AVoidProjectile : public AActor
{
	GENERATED_BODY()
	
public:	

	AVoidProjectile();

protected:

	virtual void BeginPlay() override;

	virtual void OnHit();

private:

	// TODO:: Set initial speed and max speed
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> MovementComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> BoxComponent;

public:	


};
