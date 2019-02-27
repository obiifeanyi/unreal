// A Fun open field tank game with wacky controls.

#include "TankTracks.h"

UTankTracks::UTankTracks()
{
	PrimaryComponentTick.bCanEverTick = true;
	Cast<UStaticMeshComponent>(this)->SetNotifyRigidBodyCollision(true);
}
void UTankTracks::BeginPlay()
{
	//UE_LOG(LogTemp, Warning, TEXT("IT begun"));
	OnComponentHit.AddDynamic(this, &UTankTracks::OnHit);
}

void UTankTracks::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	
	SideWaysFriction(DeltaTime);
	//On hit event
}

void UTankTracks::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp,Warning,TEXT("Hitting Floor"));
	//Can drive
	//Can add side ways friction
}

void UTankTracks::SideWaysFriction(float DeltaTime)
{
	//Calculating Side-ways force to apply friction for side-ways force. (F = ma)
	float SlippageAmount = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	auto Acceleration = -(SlippageAmount / DeltaTime * GetRightVector());
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto ForceToApply = (TankRoot->GetMass() * Acceleration) / 2;
	TankRoot->AddForce(ForceToApply);
}

void UTankTracks::SetThrottle(float speed)
{
	//set amount of force to apply
	FVector AppliedForce = GetForwardVector() * MAXSPEED * speed * GetWorld()->GetDeltaSeconds();
	FVector TrackLocation = GetComponentLocation();
	//add force
	auto RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	RootComponent->AddForceAtLocation(AppliedForce, TrackLocation);
}