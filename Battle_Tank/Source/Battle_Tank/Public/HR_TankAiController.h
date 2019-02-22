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
	//Controlled Tank
	class AHR_Tank* ControlledTank = nullptr;
	//Player Tank
	class AHR_Tank* PlayerTank = nullptr;
};
