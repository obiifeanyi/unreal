// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class BATTLE_TANK_API AProjectile : public AActor
{
	GENERATED_BODY()

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly,Category = "Firing")
		float LifeSpawnAfterCollision = 10.0f; //TODO test out other assignment methods.

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		int32 DamageAmount = 10;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ShockWaveRadius = 1500;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ExpDamageForce = 2;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float BaseDamage = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float MinimuDamage = 5.0f;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* CollisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* PrtProjectileTrail = nullptr;
	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* PrtHitExplosion = nullptr;
	UPROPERTY(VisibleAnywhere)
		class URadialForceComponent* ExplosionForce = nullptr;


public:	

	// Sets default values for this actor's properties
	AProjectile();

	//Called when tank fires.
	void LaunchProjectile(float speed);

private:

	//UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovement= nullptr;
	
	void KillActor();
	
};
