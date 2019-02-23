//Fill out your copyright notice in the Description page of Project Settings.

#include "public/HR_TankPlayerController.h"
#include "TankAimAtComponent.h"
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

void AHR_TankPlayerController::AimTowardCrossHair()
{
	if (!AimingComponent){ return; }
	FVector HitLocation; //OUT parameter
	if (GetSightAimRay(HitLocation))
	{		
		AimingComponent->TankAimAt(HitLocation);
	}
}

APawn* AHR_TankPlayerController::GetControlledTank() const
{	
	auto ControlledTank = GetPawn();
	if (!ensure(ControlledTank)) { return nullptr; }
	return ControlledTank;
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

	if (GetWorld()->LineTraceSingleByChannel(
			RayTrace, 
			Start, 
			End, 
			ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = RayTrace.Location;
		return true;
	}
	 HitLocation = FVector(0.0f);
	return false;
}