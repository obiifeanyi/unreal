// A Fun open field tank game with wacky controls.

#include "TankMovementComponent.h"
#include "TankTracks.h"

void UTankMovementComponent::IntendedMovementForward(float Throw)
{
	//UE_LOG(LogTemp, Warning, TEXT("Moving Front %f"), Throw);
	if (!LeftTrack || !RightTrack)return; //If not set in BP exit
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendedMovementTurn(float Throw)
{
	//UE_LOG(LogTemp, Warning, TEXT("Moving Front %f"), Throw);
	if (!LeftTrack || !RightTrack)return; //If not set in BP exit
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::Initialzier(UTankTracks* LeftTrack, UTankTracks* RightTrack)
{
	if(!LeftTrack || !RightTrack)return;
	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//Move Ai tank forward and backward to get to the player
	auto DesireToMoveForward = FVector::DotProduct(
			GetOwner()->GetActorForwardVector().GetSafeNormal(),
			MoveVelocity.GetSafeNormal()
		);
	IntendedMovementForward(DesireToMoveForward);

	//Turn the tank left when target is to the left
	auto DesireToTurnRight = FVector::CrossProduct(
			GetOwner()->GetActorForwardVector().GetSafeNormal(),
			MoveVelocity.GetSafeNormal()
		).Z;
	IntendedMovementTurn(DesireToTurnRight*2); //TODO the scale needed to be higher for tank to turn better.
	//UE_LOG(LogTemp, Warning, TEXT("DesireToTurnRight is %f"), DesireToTurnRight);
}

