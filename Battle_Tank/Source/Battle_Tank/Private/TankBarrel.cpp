// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include <UnrealMathUtility.h>


void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto ElevationChange = RelativeSpeed * MaxDegeePerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = RelativeRotation.Pitch + ElevationChange; //The incrementer
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegree, MaxElevationDegree);
	SetRelativeRotation(FRotator(Elevation, 0.f, 0.f));
	//UE_LOG(LogTemp, Warning, TEXT("ElevationChange is %f"), RelativeRotation.Pitch);
}