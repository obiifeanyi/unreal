// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/HR_TankAiController.h"

//begin play
void AHR_TankAiController::BeginPlay()
{
	Super::BeginPlay();
	//Setters
	ControlledTank = Cast<AHR_Tank>(GetPawn());
	PlayerTank = Cast<AHR_Tank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void AHR_TankAiController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (ControlledTank)
	{
		ControlledTank->TankAimAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire();
	}
}


