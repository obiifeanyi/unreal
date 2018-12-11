// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HR_Tank.generated.h"

UCLASS()
class BATTLE_TANK_API AHR_Tank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHR_Tank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
