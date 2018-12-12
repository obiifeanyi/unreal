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
	AimAtLocation();

	//Aim into world from CrossHair

	//get the crosshair's position on the screen
	int32 ViewportWidth, ViewportHeight;
	GetViewportSize(ViewportWidth, ViewportHeight);
	FVector2D CrossHairScreenPosition = FVector2D(ViewportWidth * 0.5, ViewportHeight * 0.3);
	

	//Convert screen position to POV direction.
	FVector WorldLocation,SightDirection;
	auto bDeprojected = DeprojectScreenPositionToWorld(CrossHairScreenPosition.X, CrossHairScreenPosition.Y, WorldLocation, SightDirection);

	FHitResult RayTrace;
	//Ray trace from cross hair to hit point in world world
	if (bDeprojected)
	{
		FVector Start = PlayerCameraManager->GetCameraLocation();
		FVector End = Start + SightDirection * Reach;
		GetWorld()->LineTraceSingleByChannel(RayTrace, Start, End, ECollisionChannel::ECC_Visibility);
	}


	UE_LOG(LogTemp, Warning, TEXT("We are hitting locatione %s"), *RayTrace.Location.ToString()) //Logging out raytrace hit location
}

AHR_Tank* AHR_TankPlayerController::GetControlledTank() const
{		
	return Cast<AHR_Tank>(GetPawn());
}


FVector AHR_TankPlayerController::AimAtLocation()
{
	
	return FVector(1.0f);
}