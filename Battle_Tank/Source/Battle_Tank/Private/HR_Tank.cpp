// Fill out your copyright notice in the Description page of Project Settings.

#include "HR_Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankTurrent.h"
#include "TankAimAtComponent.h"


// Sets default values
AHR_Tank::AHR_Tank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//
	AimingComponent = CreateDefaultSubobject<UTankAimAtComponent>(FName("AimAt Component"));
}

// Called when the game starts or when spawned
void AHR_Tank::BeginPlay()
{
	Super::BeginPlay();	
	if (!Barrel) { return; }
	AimingComponent->BarrelReference(Barrel);
}

// Called to bind functionality to input
void AHR_Tank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


//Get Hitlocation from the controller
void AHR_Tank::TankAimAt(FVector HitLocation)
{
	AimingComponent->TankAimComp(HitLocation, LauchSpeed);
}

void AHR_Tank::Fire(){

	if (!Barrel)return;	
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

void AHR_Tank::SetBarrel(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet)return;
	Barrel = BarrelToSet;
}

void AHR_Tank::SetTurrent(UTankTurrent* TurrentToSet)
{
	if (!TurrentToSet)return;
	AimingComponent->TurrentReference(TurrentToSet);
}

