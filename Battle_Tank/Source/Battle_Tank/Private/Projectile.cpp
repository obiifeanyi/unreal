// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Gameframework/ProjectileMovementComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create a projectile movement component.
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement"); //TEST using FName is the only way to make LaunchProejct to work.
	ProjectileMovement->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float speed)
{
	if (!ProjectileMovement)return;
	
	ProjectileMovement->SetVelocityInLocalSpace(FVector(FVector::ForwardVector * speed));
	ProjectileMovement->Activate();
	
}