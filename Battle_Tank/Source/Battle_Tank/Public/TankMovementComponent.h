// A Fun open field tank game with wacky controls.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTracks;
/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

	//get the tracks store in a variable
	//TODO make a function to initalize
protected:
	//make both track to move forward
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendedMovementForward(float Throw);
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendedMovementTurn(float Throw);


	UTankTracks* LeftTrack = nullptr;
	UTankTracks* RightTrack = nullptr;

private:
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)override;

public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void Initialzier(UTankTracks* LeftTrack, UTankTracks* RightTrack);

	
};
