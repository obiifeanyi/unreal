// Fill out your copyright notice in the Description page of Project Settings.

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
	void IntendedMovementTurnRight(float Throw);


	UTankTracks* LeftTrack = nullptr;
	UTankTracks* RightTrack = nullptr;

private:
public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void Initialzier(UTankTracks* LeftTrack, UTankTracks* RightTrack);

	
};
