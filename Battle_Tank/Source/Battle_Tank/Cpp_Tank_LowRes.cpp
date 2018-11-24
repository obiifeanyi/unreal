// Fill out your copyright notice in the Description page of Project Settings.

#include "Cpp_Tank_LowRes.h"


// Sets default values
ACpp_Tank_LowRes::ACpp_Tank_LowRes()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACpp_Tank_LowRes::BeginPlay()
{
	Super::BeginPlay();
	//get the barrel child actor
}

// Called every frame
void ACpp_Tank_LowRes::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACpp_Tank_LowRes::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction("RotateTurret_CW", EInputEvent::IE_Pressed, this, &ACpp_Tank_LowRes::RotateTurrent_CW);
	InputComponent->BindAction("RotateTurret_CCW", EInputEvent::IE_Pressed, this, &ACpp_Tank_LowRes::RotateTurret_CCW);

	///Set an axis input for rotation.
	//make the input.
	//input should control rotation.(Make a function at is called)
	InputComponent->BindAxis("TurrentRotate", this, &ACpp_Tank_LowRes::RotateTurrent);
	
}

void ACpp_Tank_LowRes::SetTurrent(UChildActorComponent* BarrelInput)
{
	Turrent = BarrelInput;
}

void ACpp_Tank_LowRes::RotateTurrent_CW()
{
	if (!Turrent) return;
	Turrent->AddRelativeRotation(FRotator(0.f, 45.f, 0.f));
	UE_LOG(LogTemp, Warning, TEXT("Rotating"));
	//AddLocalRotation
}

void ACpp_Tank_LowRes::RotateTurret_CCW()
{
	if (!Turrent) return;
	Turrent->AddRelativeRotation(FRotator(0.f, -45.f, 0.f));
	UE_LOG(LogTemp, Warning, TEXT("Rotating"));
}

void ACpp_Tank_LowRes::RotateTurrent(float speed)
{
	if (!Turrent)return;
	Turrent->AddRelativeRotation(FRotator(0.f, speed, 0.f));
}


