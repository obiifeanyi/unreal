// A Fun open field tank game with wacky controls.

#include "TankTracks.h"




void UTankTracks::SetThrottle(float speed)
{
	//set amount of force to apply
	FVector AppliedForce = GetForwardVector() * MAXSPEED * speed * GetWorld()->GetDeltaSeconds();
	//get where to apply the force
		//applying force at track location
	FVector TrackLocation = GetComponentLocation();
	//add force
	auto RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); //TODO test not using auto and explicitly define the type.
	RootComponent->AddForceAtLocation(AppliedForce, TrackLocation);
}