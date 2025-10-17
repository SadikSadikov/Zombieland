// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoidProjectile.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;
class UNiagaraComponent;

UENUM(BlueprintType)
enum class EProjectileType : uint8
{

	EPT_Bullet UMETA(DisplayName = "Bullet"),
	/* Deals damage with radial falloff*/
	EPT_Rocket UMETA(DisplayName = "Rocket")
};

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

	UPROPERTY(EditAnywhere, Category = "Properties")
	EProjectileType ProjectileType;
	
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
	TObjectPtr<USoundBase> ImpactSound;

	UPROPERTY(EditAnywhere, Category = "Properties|Effects")
	TObjectPtr<UParticleSystem> ImpactParticle;

public:	


};
