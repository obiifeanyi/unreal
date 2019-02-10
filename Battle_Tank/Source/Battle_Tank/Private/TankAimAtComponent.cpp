// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimAtComponent.h"
#include "TankBarrel.h"
#include "TankTurrent.h"
#include <Kismet/GameplayStatics.h>



// Sets default values for this component's properties
UTankAimAtComponent::UTankAimAtComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTankAimAtComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UTankAimAtComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

EFiringState UTankAimAtComponent::GetFiringState() const
{
	return FiringState;
}

void UTankAimAtComponent::BarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet)return;
	Barrel = BarrelToSet;
}

void UTankAimAtComponent::TurrentReference(UTankTurrent* TurrentToSet)
{
	if (!TurrentToSet)return;
	Turrent = TurrentToSet;
}

void UTankAimAtComponent::TankAimComp(FVector AimAt,float LauchSpeed)
{
	if (!Barrel)return;

	FVector OutProjectileVelocity = FVector(1.0f); //OUT
	FVector Startlocation = Barrel->GetSocketLocation(FName("ProjectileStart")); //Socket location of barrel.
	FVector Endlocation = AimAt; //Hit location of project.
	bool bHasAim = UGameplayStatics::SuggestProjectileVelocity
		(
			this,
			OutProjectileVelocity,
			Startlocation,
			Endlocation,
			LauchSpeed,																		  
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace
		);

	FVector AimDirection = OutProjectileVelocity.GetSafeNormal();

	
	if(bHasAim)
	{
		MoveBarrelTowards(AimDirection);		
	}
}

void UTankAimAtComponent::MoveBarrelTowards(FVector AimDirection)
{
	//Workout difference between current rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	if (!Turrent)return;
	Turrent->Yaw(DeltaRotator.Yaw);
	if (!Barrel)return;
	Barrel->Elevate(DeltaRotator.Pitch);
}