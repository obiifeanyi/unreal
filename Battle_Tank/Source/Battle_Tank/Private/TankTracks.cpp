// A Fun open field tank game with wacky controls.

#include "TankTracks.h"

UTankTracks::UTankTracks()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTracks::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	
	//Calculating Side-ways force to apply friction for side-ways force. (F = ma)
	float SlippageAmount = FVector::DotProduct(GetComponentVelocity(),GetRightVector());
	float Acceleration = SlippageAmount/DeltaTime;
	float TankMass = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent())->GetMass();
	auto ForceToApply = -(TankMass * Acceleration * GetRightVector());
	UE_LOG(LogTemp, Warning, TEXT("component right vector %f"), SlippageAmount); //TODO why is 
	//AddForceAtLocation(ForceToApply,GetOwner()->GetRootComponent()->GetComponentLocation());
}

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