// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurrent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hideCategories = ("Collision", "Physics") )
class BATTLE_TANK_API UTankTurrent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	public:
		// +1 to -1 to elevate or lower the barrel.
		void Yaw(float RelativeSpeed);

	private:
		UPROPERTY(EditAnywhere)
			float MaxDegeePerSecond = 35.f; //TODO find insensible value.
		

	
	
	
};
