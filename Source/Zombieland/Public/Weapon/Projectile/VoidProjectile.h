// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoidProjectile.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class ZOMBIELAND_API AVoidProjectile : public AActor
{
	GENERATED_BODY()
	
public:	

	AVoidProjectile();

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void Destroyed() override;

	void SpawnTrailSystem();
	
private:
	
	void StartDestroyTimer();

	void DestroyTimerFinished();
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> MovementComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(EditAnywhere, Category = "Properties")
	float InitialSpeed = 15000;

	UPROPERTY(EditAnywhere)
	float DestroyTime = 10.f;

	FTimerHandle DestroyTimer;

	// Effect

	UPROPERTY()
	TObjectPtr<UParticleSystemComponent> TracerComponent;

	UPROPERTY(EditAnywhere, Category = "Properties|Effects")
	TObjectPtr<UParticleSystem> TracerParticle;

	UPROPERTY(EditAnywhere, Category = "Properties|Effects")
	TObjectPtr<UNiagaraSystem> TrailSystem;

	UPROPERTY(EditAnywhere, Category = "Properties|Effects")
	TObjectPtr<UNiagaraComponent> TrailSystemComponent;

	UPROPERTY(EditAnywhere, Category = "Properties|Effects")
	TObjectPtr<UParticleSystem> ImpactParticle;

	UPROPERTY(EditAnywhere, Category = "Properties|Effects")
	TObjectPtr<USoundBase> ImpactSound;

public:	


};
