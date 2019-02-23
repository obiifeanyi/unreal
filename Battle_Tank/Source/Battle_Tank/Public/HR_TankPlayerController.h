// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HR_TankPlayerController.generated.h"

class TankAimAtComponent;

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
	class APawn* GetControlledTank() const;

	//Blueprint Event to find Aiming Component
	UFUNCTION(BlueprintImplementableEvent,Category = "SetUp")
	void FoundAimingComponent(UTankAimAtComponent* AimingCompRef);

	//Components pointers
	UPROPERTY(BlueprintReadOnly)
	class UTankAimAtComponent* AimingComponent;


private:


	//Returns the cross hair position in relation to realworld.
	void AimTowardCrossHair();

	//return true if hit point in world and OUT a value parameter to hitLocation.
	bool GetSightAimRay(FVector& HitLocation) const;

	bool GetLookDirection(FVector2D ScreenPosition, FVector& LookAtDirection) const;

	bool RayTraceLookDirectionToHitLocation(FVector, FVector&)const;

	UPROPERTY(EditAnywhere, category = "Tank")
		float Reach = 1000000;

	UPROPERTY(EditAnywhere, category = "Tank")
		float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere, category = "Tank")
		float CrossHairYLocation = 0.4;

};