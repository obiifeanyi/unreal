// Fill out your copyright notice in the Description page of Project Settings.

#include "HR_Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankTurrent.h"
#include "TankAimAtComponent.h"
//#include <GameFramework/Actor.h>


// Sets default values
AHR_Tank::AHR_Tank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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


// Called to bind functionality to input
void AHR_Tank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &AHR_Tank::Fire);
}


//Tank Aim At system get Hitlocation from Controller Actor and uses it to aim tank in a direction.
void AHR_Tank::TankAimAt(FVector HitLocation)
{
	AimingComponent->TankAimComp(HitLocation, LauchSpeed);
}

void AHR_Tank::Fire()
{

	if (!Barrel)return;
	FTransform SpawnTransform = FTransform(
		Barrel->GetSocketRotation("ProjectileStart"),
		Barrel->GetSocketLocation("ProjectileStart")
		);

	FVector Location(0.0f, 0.0f, 50.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	//GetWorld()->SpawnActor<AProjectile>(BP_Projectile,Location, Rotation, SpawnInfo);
	GetWorld()->SpawnActor<AProjectile>(BPProjectile, Barrel->GetSocketLocation("ProjectileStart"), Barrel->GetSocketRotation("ProjectileStart"), SpawnInfo);

	
	UE_LOG(LogTemp, Warning, TEXT("Hello %f"), GetWorld()->GetTimeSeconds());

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

