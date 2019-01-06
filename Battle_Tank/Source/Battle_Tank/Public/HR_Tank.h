// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HR_Tank.generated.h"

class UTankAimAtComponent;

UCLASS()
class BATTLE_TANK_API AHR_Tank : public APawn
{
	GENERATED_BODY()

private:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//Static mesh barrel from tank
	UStaticMeshComponent* Barrel = nullptr;

public:
	// Sets default values for this pawn's properties
	AHR_Tank();

	void TankAimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Tank")
	void SetBarrel(UStaticMeshComponent* BarrelToSet);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Make default components
	UTankAimAtComponent* AimingComponent = nullptr;
	//The launch velocity of projectile
	UPROPERTY(EditAnywhere)
		float LauchSpeed = 1000; // TODO Find sensible value	



	
};
