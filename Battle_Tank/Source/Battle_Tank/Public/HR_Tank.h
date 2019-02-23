// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HR_Tank.generated.h"


class AProjectile;

UCLASS()
class BATTLE_TANK_API AHR_Tank : public APawn
{
	GENERATED_BODY()

private:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
		
public:

	// Sets default values for this pawn's properties
		AHR_Tank();

protected:
	
	//
		virtual void BeginPlay() override;
	
	//The Aiming component Use to Turn the barrel
		UPROPERTY(BlueprintReadOnly)
		class UTankAimAtComponent* AimingComponent;  //Remove when refractoring fire
};