// Fill out your copyright notice in the Description page of Project Settings.

#include "public/HR_TankPlayerController.h"


void AHR_TankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	//UE_LOG(LogTemp, Warning, TEXT("The Possessed Tank is %s"), *ControlledTank->GetName());	//Log possessed tank name
}

void AHR_TankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

// //Aim into world from CrossHair
// 		//get the crosshair's position on the screen
// 		int32 ViewportWidth, ViewportHeight;
// 		GetViewportSize(ViewportWidth, ViewportHeight);
// 		FVector2D CrossHairScreenPosition = FVector2D(ViewportWidth *CrossHairXLocation, ViewportHeight * CrossHairYLocation);
// 		
// 	
// 		//Convert screen position to POV direction.
// 		FVector WorldLocation,SightDirection;
// 		auto bDeprojected = DeprojectScreenPositionToWorld(CrossHairScreenPosition.X, CrossHairScreenPosition.Y, WorldLocation, SightDirection);
// 	
// 		FHitResult RayTrace;
// 		FVector HitLocation;
// 		//Ray trace from cross hair to hit point in world world
// 		if (bDeprojected)
// 		{
// 			FVector Start = PlayerCameraManager->GetCameraLocation();
// 			FVector End = Start + SightDirection * Reach;
// 			
// 			if (GetWorld()->LineTraceSingleByChannel(RayTrace, Start, End, ECollisionChannel::ECC_Visibility)) //Set Hitlocation to raytrace location
// 			{
// 				HitLocation = RayTrace.Location;
// 			}
// 			else HitLocation = FVector(0.0f); //Hitlocation out of bounds.
// 		}
// 		UE_LOG(LogTemp, Warning, TEXT("We are hitting location %s"), *HitLocation.ToString()) //Logging out raytrace hit location
// 		
// 		//Calling Control Tank function
// 		AHR_Tank* ControllerTank = GetControlledTank();
// 		if (ControllerTank)
// 		{
// 			ControllerTank->TankAimAt(HitLocation);
// 		}

	AimTowardCrossHair();

}

AHR_Tank* AHR_TankPlayerController::GetControlledTank() const
{	
	auto ControlledTank = GetPawn();
	if (!ControlledTank) { return nullptr; }
	return Cast<AHR_Tank>(ControlledTank);
}

void AHR_TankPlayerController::AimTowardCrossHair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; //OUT parameter
	if (GetSightAimRayHitLocation(HitLocation))
	{
		GetControlledTank()->TankAimAt(HitLocation);
	}
}

bool AHR_TankPlayerController::GetSightAimRayHitLocation(FVector& HitLocation) const
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
			//UE_LOG(LogTemp, Warning, TEXT("The LookAtDirection is %s"), *LookAtDirection.ToString());
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