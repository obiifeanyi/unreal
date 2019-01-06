// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimAtComponent.h"
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
			LauchSpeed/*,																		  Should be buggy.
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace*/
		);

	FVector AimDirection = OutProjectileVelocity.GetSafeNormal();

	//UE_LOG(LogTemp, Warning, TEXT("ProjectileVelocity at is here %s with this LauchSpeed %f"),*OutProjectileVelocity.ToString(),LauchSpeed)
	if(bHasAim)
	{
		UE_LOG(LogTemp, Warning, TEXT("Aimat at is here %s with this LauchSpeed %f"), *AimDirection.ToString(), LauchSpeed)
		MoveBarrelTowards(AimDirection);
	}

}

void UTankAimAtComponent::BarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimAtComponent::MoveBarrelTowards(FVector AimDirection)
{
	//get initial position
	FRotator BarrelInitialRotation = Barrel->GetForwardVector().Rotation();
	//Find delta between initial rotation and desired rotation
	FRotator deltaRotation = BarrelInitialRotation - AimDirection.Rotation();
	//Use the Delta rotation to move barrel.
	//move barrel to desired position
	Barrel->AddLocalRotation(deltaRotation);
}
