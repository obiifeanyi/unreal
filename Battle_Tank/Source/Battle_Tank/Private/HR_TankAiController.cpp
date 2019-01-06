// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/HR_TankAiController.h"

//begin play
void AHR_TankAiController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	auto PlayerTank = GetPlayerTank();

	if (!PlayerTank || !ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled tank is Can't find player thank"));
	}
 	else
 	{
 		UE_LOG(LogTemp, Warning, TEXT("Controlled tank is %s and the player is %s"), *(ControlledTank->GetName()), *(PlayerTank->GetName()));
 	}

}

void AHR_TankAiController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (GetPlayerTank())
	{
		//GetControlledTank()->TankAimAt(GetPlayerTank()->GetActorLocation());												  commented to stop AI tanks from logging.
	}
}


AHR_Tank * AHR_TankAiController::GetControlledTank() const
{
	return Cast<AHR_Tank>(GetPawn());
}

AHR_Tank* AHR_TankAiController::GetPlayerTank() const
{
	auto PlayerPawn =GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<AHR_Tank>(PlayerPawn);
	return nullptr;
}
