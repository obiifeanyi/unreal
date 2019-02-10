// Fill out your copyright notice in the Description page of Project Settings.

#include "HR_Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankTurrent.h"
#include "TankAimAtComponent.h"
#include "TankMovementComponent.h"


// Sets default values
AHR_Tank::AHR_Tank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AHR_Tank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void AHR_Tank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


//Get Hitlocation from the controller
void AHR_Tank::TankAimAt(FVector HitLocation)
{
	if(!AimingComponent)return;
	AimingComponent->TankAimComp(HitLocation, LauchSpeed);
}

void AHR_Tank::Fire(){

	//TODO Protect the Fire function
	FActorSpawnParameters SpawnInfo;
	//GetWorld()->SpawnActor<AProjectile>(BP_Projectile,Location, Rotation, SpawnInfo);
	auto Projectile = GetWorld()->SpawnActor<AProjectile>
		(
			BPProjectile,
			Barrel->GetSocketLocation("ProjectileStart"),
			Barrel->GetSocketRotation("ProjectileStart"),
			SpawnInfo
		);
	//
	Projectile->LaunchProjectile(LauchSpeed);
}


