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
	
	InputComponent->BindAxis("TurrentRotate", this, &ACpp_Tank_LowRes::RotateTurrent);
	InputComponent->BindAxis("BarrelRotate", this, &ACpp_Tank_LowRes::RotateBarrel);
	InputComponent->BindAxis("BodyMove", this, &ACpp_Tank_LowRes::MoveBody);
	InputComponent->BindAxis("BodyRotate", this, &ACpp_Tank_LowRes::RotateBody);
	
}


///Setter Functions
void ACpp_Tank_LowRes::SetTurrent(UChildActorComponent* TurrentInput)
{
	if (!TurrentInput) { return; }
	Turrent = TurrentInput;
}
void ACpp_Tank_LowRes::SetBarrel(UChildActorComponent* BarrelInput)
{
	if (!BarrelInput) { return; }
	Barrel = BarrelInput;
}
void ACpp_Tank_LowRes::SetBody(UChildActorComponent* BodyInput)
{
	if (!BodyInput) { return;}
	Body = BodyInput;
}


///Movements Functions
void ACpp_Tank_LowRes::RotateTurrent(float speed)
{
	if (!Turrent)return;
	Turrent->AddRelativeRotation(FRotator(0.f, speed, 0.f));
}
void ACpp_Tank_LowRes::RotateBarrel(float speed)
{
	if (!Barrel)return;
	Barrel->AddRelativeRotation(FRotator(speed,0.f,0.f));
}
void ACpp_Tank_LowRes::MoveBody(float speed)
{
	if (!Body) { return; }
	Body->AddRelativeLocation(Body->GetForwardVector()*speed*GetMovenementScale());
}
void ACpp_Tank_LowRes::RotateBody(float speed)
{
	if (!Body) { return; }
	Body->AddRelativeRotation(FRotator(0.f, speed, 0.f));
}

//Movement Scale
float ACpp_Tank_LowRes::GetMovenementScale() const
{
	return MovementScale;
}

