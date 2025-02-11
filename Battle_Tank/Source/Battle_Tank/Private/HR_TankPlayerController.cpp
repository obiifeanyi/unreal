//Fill out your copyright notice in the Description page of Project Settings.

#include "public/HR_TankPlayerController.h"
#include "TankAim_Component/TankAimAtComponent.h"
#include "HR_Tank.h"

void AHR_TankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	GetControlledTank();
	
	//Blueprint Event AimingCompnent filled out
	AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimAtComponent>();
	if (AimingComponent){FoundAimingComponent(AimingComponent);}
}

void AHR_TankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	AimTowardCrossHair();
}

void AHR_TankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		AHR_Tank* Possessed = Cast<AHR_Tank>(GetPawn());
		if (!ensure(Possessed))return;
		Possessed->TankDeath.AddUniqueDynamic(this,&AHR_TankPlayerController::OnTankDeath);
	}
}

void AHR_TankPlayerController::OnTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Dead"));
	if(!ensure(GetPawn()))return;
	StartSpectatingOnly();
}

void AHR_TankPlayerController::AimTowardCrossHair()
{
	if (!AimingComponent){ return; }
	FVector HitLocation; //OUT parameter
	bool bGotHitLocation = GetSightAimRay(HitLocation);
	if (bGotHitLocation)
	{		
		AimingComponent->TankAimAt(HitLocation);
	}
}

APawn* AHR_TankPlayerController::GetControlledTank() const
{	
	if (!ensure(GetPawn())){ return nullptr;}

	return GetPawn();
}


bool AHR_TankPlayerController::GetSightAimRay(FVector& HitLocation) const
{
	//Get 2d location of cross hair on screen
	int32 ViewportWidth, ViewportHeight;
	GetViewportSize(ViewportWidth, ViewportHeight);
	auto CrossHairScreenPosition = FVector2D(ViewportWidth *CrossHairXLocation, ViewportHeight * CrossHairYLocation);


	// Get the look at direction in the world
	FVector LookAtDirection;
	if (GetLookDirection(CrossHairScreenPosition,LookAtDirection))
	{
		if (RayTraceLookDirectionToHitLocation(LookAtDirection, HitLocation))
		{
			return true;
		}

	}

	HitLocation = FVector(1.0f); 
	return false;
}

// OUTs a look at direction and returns true if successed.
bool AHR_TankPlayerController::GetLookDirection(FVector2D ScreenPosition, FVector& LookAtDirection)const
{
	FVector WorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenPosition.X,
		ScreenPosition.Y,
		WorldLocation,
		LookAtDirection
	);
}

bool AHR_TankPlayerController::RayTraceLookDirectionToHitLocation(FVector LookDirection, FVector& HitLocation)const
{

	//Ray-trace LookDirection to point in World
	FHitResult RayTrace;	 		
	FVector Start = PlayerCameraManager->GetCameraLocation();
	FVector End = Start + LookDirection * Reach;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetPawn());
	bool bGotHitResult = GetWorld()->LineTraceSingleByChannel(RayTrace, Start, End, ECollisionChannel::ECC_Visibility, CollisionParams);
	
	if (bGotHitResult)
	{
		HitLocation = RayTrace.Location;
		return true;
	}
	 HitLocation = FVector(0.0f);
	return false;
}