// A Fun open field tank game with wacky controls.

#include "../Public/HR_TankAiController.h"
#include "TankAim_Component/TankAimAtComponent.h"
#include "HR_Tank.h"
//Indirectly dependency on TankMovment component Navigation mesh.


//begin play
void AHR_TankAiController::BeginPlay()
{
	Super::BeginPlay();
	
	ControlledTank = GetPawn();
	PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (ensure(ControlledTank || PlayerTank)) {
	AimingComponent = ControlledTank->FindComponentByClass<UTankAimAtComponent>();
	}
}

void AHR_TankAiController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	//Get the pawn
	if (InPawn) {
		auto PossessedTank = Cast<AHR_Tank>(GetPawn());
		PossessedTank->TankDeath.AddUniqueDynamic(this, &AHR_TankAiController::TankDeath);
	}
}

void AHR_TankAiController::TankDeath()
{
	if (!ensure(GetPawn())) return;
	GetPawn()->DetachFromControllerPendingDestroy();
}

void AHR_TankAiController::Tick(float DeltaSeconds)
{

	Super::Tick(DeltaSeconds);

	if (AimingComponent)
	{
		AimingComponent->TankAimAt(PlayerTank->GetActorLocation());
		
		if (AimingComponent->GetFiringState() == EFiringState::Locked)
		{
			AimingComponent->Fire();
		}
	}

	MoveToActor(PlayerTank,AcceptanceRadiusTankMovement); //TODO make it a UProperty and test with BP version
}




