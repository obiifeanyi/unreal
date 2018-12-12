// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HR_Tank.h"
#include "GameFramework/PlayerController.h"
#include "HR_TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_TANK_API AHR_TankPlayerController : public APlayerController
{
	GENERATED_BODY()
	


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;


private:
	AHR_Tank* GetControlledTank() const;


	UPROPERTY(EditAnywhere, category = "Tank")
		float Reach = 100000;

public:
	///Will make the tank's turrent turn and look at a position
	FVector AimAtLocation();
	
};
