// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurrent.h"

void UTankTurrent::Yaw(float RelativeSpeed)
{
	auto YawChange = RelativeSpeed * MaxDegeePerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewYaw = RelativeRotation.Yaw + YawChange; //The incrementer
	SetRelativeRotation(FRotator(0.f, RawNewYaw , 0.f));
	//UE_LOG(LogTemp, Warning, TEXT("YawChange is %f"), RelativeRotation.Pitch);
}


