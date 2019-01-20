// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurrent.h"

void UTankTurrent::Yaw(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto YawChange = RelativeSpeed * MaxDegeePerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewYaw = RelativeRotation.Yaw + YawChange; //The incrementer
	SetRelativeRotation(FRotator(0.f, RawNewYaw , 0.f));
}


