// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HR_Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "HR_TankAiController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_TANK_API AHR_TankAiController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	AHR_Tank* GetPlayerTank() const;
	
private:

	//Get the controlled Tank of the AI
	AHR_Tank* GetControlledTank() const;


	

	
	
};
