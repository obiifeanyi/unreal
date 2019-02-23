// A Fun open field tank game with wacky controls.

#include "../Public/HR_TankAiController.h"
#include "TankAimAtComponent.h"
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

void AHR_TankAiController::Tick(float DeltaSeconds)
{

	Super::Tick(DeltaSeconds);

	if (AimingComponent)
	{
		AimingComponent->TankAimAt(PlayerTank->GetActorLocation());
		AimingComponent->Fire();
	}

	
	MoveToActor(PlayerTank,1000);

}




