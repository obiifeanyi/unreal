// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 Static Mesh Component of Barrel of Tank
 */

UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hideCategories = ("Collision", "Physics") )
class BATTLE_TANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// +1 to -1 to elevate or lower the barrel.
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere)
		float MaxDegeePerSecond = 20.f; //TODO find insensible value.
	UPROPERTY(EditAnywhere)
		float MaxElevationDegree = 50.f; //TODO set ideal
	UPROPERTY(EditAnywhere)
		float MinElevationDegree = 0.f; //TODO set ideal
};
