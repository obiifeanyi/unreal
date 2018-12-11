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

private:
	AHR_Tank* GetControlledTank() const;
	
	
};
