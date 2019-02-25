// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimAtComponent.h"
#include "TankBarrel.h"
#include "TankTurrent.h"
#include "Projectile.h"
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
	LastReloadTime = FPlatformTime::Seconds();
	
}

void UTankAimAtComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurrent* TurrentToSet)
{
	if(!(BarrelToSet || TurrentToSet))return;
	Barrel = BarrelToSet;
	Turrent = TurrentToSet;
}

// Called every frame
void UTankAimAtComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	//SetCanFire(FiringRate);

	if ((FPlatformTime::Seconds() - LastReloadTime) < FiringRate){ 
		FiringState = EFiringState::Reloading;
	}
	else if (!(IsBarrelMoving())){
		FiringState = EFiringState::Aim;
	}
	else{
		FiringState = EFiringState::Locked;
	}
}

bool UTankAimAtComponent::IsBarrelMoving()
{
	auto BarrelForward = Barrel->GetForwardVector();
	return BarrelForward.Equals(AimDirection,0.05);
}

void UTankAimAtComponent::TankAimAt(FVector AimAt)
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

	AimDirection = OutProjectileVelocity.GetSafeNormal();

	
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

	//	Moves the Turrent and Barrel
	if (!Turrent)return;
	Turrent->Yaw(DeltaRotator.Yaw); //Calls function on Turrent
	if (!Barrel)return;
	Barrel->Elevate(DeltaRotator.Pitch);

	//Set Firing State to Locked
// 	if(BarrelRotator.Equals(AimAsRotator,5)){
// 		FiringState = EFiringState::Locked; // TODO remove from here it is constant being override by Aim
// 	}
	//UE_LOG(LogTemp, Warning, TEXT("Locked %s"),BarrelRotator.Equals(AimAsRotator, 5) ? TEXT("True") : TEXT("False"))
}

void UTankAimAtComponent::SetCanFire(float RatePerSecond)
{

	float Timer = GetWorld()->GetTimeSeconds();

	//Reset the clock
	if (JustFired){
		OffsetTimer = Timer;
		JustFired = false;
	}

	//Can the tank fire
	Counter = Timer - OffsetTimer;
	
	if (Counter > RatePerSecond){
		bCanFire = true;
		FiringState = EFiringState::Aim; //TODO remove and set in Firing state function
	}
	else{
		bCanFire = false;
		FiringState = EFiringState::Reloading; //TODO remove and set in Firing state function
	}

}

//Fire Out a Projectile.
void UTankAimAtComponent::Fire() {

	if (!ensure(Barrel || BPProjectile))return;


	if(FiringState != EFiringState::Reloading) //TODO if want to use SetCanFire function change to bCanFire variable.
	{
		FActorSpawnParameters SpawnInfo;
		auto Projectile = GetWorld()->SpawnActor<AProjectile>
			(
				BPProjectile,
				Barrel->GetSocketLocation("ProjectileStart"),
				Barrel->GetSocketRotation("ProjectileStart"),
				SpawnInfo
			);
		//Launch the created projectile
		Projectile->LaunchProjectile(LauchSpeed);
		JustFired = true; //Reset counter in SetCanFire

		LastReloadTime = FPlatformTime::Seconds();
	}

}

//
EFiringState UTankAimAtComponent::GetFiringState() const
{
	return FiringState;
}
