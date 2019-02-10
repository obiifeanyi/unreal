// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HR_Tank.generated.h"

class UTankAimAtComponent;
class UTankBarrel;
class UTankTurrent;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class BATTLE_TANK_API AHR_Tank : public APawn
{
	GENERATED_BODY()

private:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//Static mesh barrel from tank
	UTankBarrel* Barrel = nullptr;
	//Projectile from tank
	UPROPERTY(EditAnywhere, Category = "Tank")
		TSubclassOf<AProjectile> BPProjectile;
	//
	UPROPERTY(EditAnywhere, Category = "Tank")
		float LauchSpeed = 1000; // TODO Find sensible value
public:
	// Sets default values for this pawn's properties
	AHR_Tank();
	//
	void TankAimAt(FVector HitLocation);
	//
	UFUNCTION(BlueprintCallable, Category = "Tank")
	void SetBarrel(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = "Tank")
	void SetTurrent(UTankTurrent* TurrentToSet);

	UFUNCTION(BlueprintCallable, Category = "Tank")
	void Fire();
protected:

	virtual void BeginPlay() override;
	//
	UPROPERTY(BlueprintReadOnly)
	UTankAimAtComponent* AimingComponent = nullptr;
	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* MovementComponent = nullptr;
	
};