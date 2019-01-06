// Fill out your copyright notice in the Description page of Project Settings.

#include "HR_Tank.h"
#include "TankAimAtComponent.h"


// Sets default values
AHR_Tank::AHR_Tank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//construct component
	AimingComponent = CreateDefaultSubobject<UTankAimAtComponent>(FName("AimAtComponent"));

}

// Called when the game starts or when spawned
void AHR_Tank::BeginPlay()
{
	Super::BeginPlay();
	
	//Setting Barrel reference for Aiming component
	if (!Barrel) { return; }
	AimingComponent->BarrelReference(Barrel);
}

// Called every frame
void AHR_Tank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AHR_Tank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


//Tank Aim At system get Hitlocation from Controller Actor and uses it to aim tank in a direction.
void AHR_Tank::TankAimAt(FVector HitLocation)
{
	AimingComponent->TankAimComp(HitLocation, LauchSpeed);
}

void AHR_Tank::SetBarrel(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}
