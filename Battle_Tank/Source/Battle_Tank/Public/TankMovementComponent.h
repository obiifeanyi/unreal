// A Fun open field tank game with wacky controls.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTracks;
/**
	Handle the Forward and Rotational movement of the tank around the world.
	The AI tank uses the same movement mechanism. The data from NavMovementComponent is used
	as driving force to throw.
 */
UCLASS()
class BATTLE_TANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
protected:
	//Throws -1 to 1 into the throttle component to move the tank forward or back
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendedMovementForward(float Throw);
	//Throws -1 to 1 into the throttle component to turn the tank left or right
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendedMovementTurn(float Throw);

private:
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)override; //For AI tanks to navigate.
	UTankTracks* LeftTrack = nullptr;
	UTankTracks* RightTrack = nullptr;

public:
	//SetsUp the Left and Right Throttle components so function can be called of it.
	UFUNCTION(BlueprintCallable, Category = "SetUp")
	void Initialzier(UTankTracks* LeftTrack, UTankTracks* RightTrack);

	
};
