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

void UTankAimAtComponent::TankAimComp(FVector AimAt,float LauchSpeed)
{

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
		//UE_LOG(LogTemp, Warning, TEXT("Aimat at is here %s with this LauchSpeed %f"), *AimDirection.ToString(), LauchSpeed)
		MoveBarrelTowards(AimDirection);
		
	}

}

void UTankAimAtComponent::BarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimAtComponent::TurrentReference(UTankTurrent* TurrentToSet)
{
	Turrent = TurrentToSet;
}

void UTankAimAtComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!Turrent)return;
	Turrent->Yaw(1);

	if (!Barrel)return;
	Barrel->Elevate(1);

}

// FRotator BarrelInitialRotation = Barrel->GetForwardVector().Rotation();
// FRotator deltaRotation = BarrelInitialRotation - AimDirection.Rotation();
// move barrel to desired position
// Barrel->AddLocalRotation(deltaRotation);
// FRotator BarrelRotation = FRotator(AimDirection.Rotation().Pitch, 0.f, 0.f);
// Barrel->SetRelativeRotation(BarrelRotation);
// UE_LOG(LogTemp, Warning, TEXT("Help Me ME ME"));