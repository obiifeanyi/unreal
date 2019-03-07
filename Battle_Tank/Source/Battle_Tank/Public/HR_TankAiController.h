// A Fun open field tank game with wacky controls.

#pragma once


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


private:
	
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetPawn(APawn* InPawn) override;

	//Controlled Tank
	class APawn* ControlledTank = nullptr;

	//Player Tank
	class APawn* PlayerTank = nullptr;

protected:

	UFUNCTION()
		void TankDeath();

	//How close the Tank can get to me.
	UPROPERTY(EditAnywhere, Category = "Movement")
		float AcceptanceRadiusTankMovement = 2000.0f;

	//Getting access to the Aim component found on Possessed Tank
	class UTankAimAtComponent* AimingComponent;

};
