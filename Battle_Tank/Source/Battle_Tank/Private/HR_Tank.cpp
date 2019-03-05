// Fill out your copyright notice in the Description page of Project Settings.

#include "HR_Tank.h"


// Sets default values
AHR_Tank::AHR_Tank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//UE_LOG(LogTemp,Warning,TEXT("DONKEY:Tank_cpp Constructor")) //TODO which is called first BP or code
}

// Called when the game starts or when spawned
void AHR_Tank::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("DONKEY:Tank_cpp BeginPlay"))
}

// Called to bind functionality to input
void AHR_Tank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

//Take damage event reduces health of player.
float AHR_Tank::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);


	//Player health decreased by damage
	PlayerHealth = FMath::Clamp<int32>(PlayerHealth - int32(Damage),0,PlayerHealth);

	UE_LOG(LogTemp, Warning, TEXT("Player's is %i"), PlayerHealth);
	return Damage;
}

