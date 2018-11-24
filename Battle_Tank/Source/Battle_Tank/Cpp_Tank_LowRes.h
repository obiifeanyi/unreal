// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Cpp_Tank_LowRes.generated.h"

UCLASS()
class BATTLE_TANK_API ACpp_Tank_LowRes : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACpp_Tank_LowRes();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	//Variables
	UChildActorComponent* Turrent = nullptr;


	//Functions
	UFUNCTION(BlueprintCallable,Category="Tank")
	void SetTurrent(UChildActorComponent* Turrent);

	void RotateTurrent_CW();
	void RotateTurret_CCW();
	void RotateTurrent(float speed);
	
};
