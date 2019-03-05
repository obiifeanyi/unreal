// A Fun open field tank game with wacky controls.

#include "TankTracks.h"

UTankTracks::UTankTracks()
{
	PrimaryComponentTick.bCanEverTick = false;
	Cast<UStaticMeshComponent>(this)->SetNotifyRigidBodyCollision(true);
}
void UTankTracks::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTracks::OnHit);
}

void UTankTracks::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp,Warning,TEXT("Throttle is %f"), Throttle);
	DriveThrottle();
	//SideWaysFriction();
	Throttle = 0; //Reset Throttle
}

void UTankTracks::SideWaysFriction()
{
	//Calculating Side-ways force to apply friction for side-ways force. (F = ma)
	float SlippageAmount = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	auto Acceleration = -(SlippageAmount / DeltaTime * GetRightVector());
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto ForceToApply = (TankRoot->GetMass() * Acceleration) / 2;
	TankRoot->AddForce(ForceToApply);
}

void UTankTracks::SetThrottle(float speed)
{
	Throttle = FMath::Clamp<float>(Throttle + speed,-1,1);  //TODO fix throttle hanging problem.
}

void UTankTracks::DriveThrottle()
{
	//set amount of force to apply
	FVector AppliedForce = GetForwardVector() * MAXSPEED * Throttle * GetWorld()->GetDeltaSeconds();
	FVector TrackLocation = GetComponentLocation();
	//add force
	auto RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	RootComponent->AddForceAtLocation(AppliedForce, TrackLocation);
}