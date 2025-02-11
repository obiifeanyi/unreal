// A Fun open field tank game with wacky controls.

#include "TankMovementComponent.h"
#include "TankTracks.h"
//Depends on Inputs from human. BP

void UTankMovementComponent::Initialzier(UTankTracks* LeftTrack, UTankTracks* RightTrack)
{
	if(!ensure(LeftTrack && RightTrack))return;
	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto DesireToMoveForward = FVector::DotProduct(
			GetOwner()->GetActorForwardVector().GetSafeNormal(),
			MoveVelocity.GetSafeNormal()
		);
	IntendedMovementForward(DesireToMoveForward);

	auto DesireToTurn = FVector::CrossProduct(
			GetOwner()->GetActorForwardVector().GetSafeNormal(),
			MoveVelocity.GetSafeNormal()
		).Z;
	IntendedMovementTurn(DesireToTurn*2); //TODO the scale needed to be higher for tank to turn better.
}

void UTankMovementComponent::IntendedMovementForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack))return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendedMovementTurn(float Throw)
{
	if (!ensure(LeftTrack && RightTrack))return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}



