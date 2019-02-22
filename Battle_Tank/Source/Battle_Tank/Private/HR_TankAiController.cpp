// A Fun open field tank game with wacky controls.

#include "../Public/HR_TankAiController.h"
#include "HR_Tank.h"
//Indirectly dependency on TankMovment component Navigation mesh.


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
		//ControlledTank->Fire();
	}

	
	MoveToActor(PlayerTank,1000);

}




