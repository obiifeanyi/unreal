// Fill out your copyright notice in the Description page of Project Settings.

#include "public/HR_TankPlayerController.h"


void AHR_TankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	UE_LOG(LogTemp, Warning, TEXT("The Possessed Tank is %s"), *ControlledTank->GetName());
}

AHR_Tank* AHR_TankPlayerController::GetControlledTank() const
{	
	return Cast<AHR_Tank>(GetPawn());
}