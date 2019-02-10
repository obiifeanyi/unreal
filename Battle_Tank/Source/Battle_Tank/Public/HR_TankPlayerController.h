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
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	AHR_Tank* GetControlledTank() const;

private:


	//Returns the cross hair position in relation to realworld.
	void AimTowardCrossHair();

	//return true if hit point in world and OUT a value parameter to hitLocation.
	bool GetSightAimRay(FVector& HitLocation) const;

	bool GetLookDirection(FVector2D ScreenPosition, FVector& LookAtDirection) const;

	bool RayTraceLookDirectionToHitLocation(FVector, FVector&)const;

	UPROPERTY(EditAnywhere, category = "Tank")
		float Reach = 1000000; //TODO Reach should be a Tank pawn property that is public.

	UPROPERTY(EditAnywhere, category = "Tank")
		float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere, category = "Tank")
		float CrossHairYLocation = 0.333;


public:
	

};