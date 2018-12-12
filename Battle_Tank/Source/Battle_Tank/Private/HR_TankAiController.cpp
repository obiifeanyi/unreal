// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/HR_TankAiController.h"

//begin play
void AHR_TankAiController::BeginPlay()
{
	Super::BeginPlay();
	AHR_Tank* ControlledTank = GetControlledTank();
	AHR_Tank* PlayerTank = GetPlayerTank();
	UE_LOG(LogTemp, Warning, TEXT("Controlled tank is %s and the player is %s"), *(ControlledTank->GetName()),*(GetPlayerTank()->GetName()));
	
}


AHR_Tank * AHR_TankAiController::GetControlledTank() const
{
	return Cast<AHR_Tank>(GetPawn());
}

AHR_Tank* AHR_TankAiController::GetPlayerTank() const
{
	return Cast<AHR_Tank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
