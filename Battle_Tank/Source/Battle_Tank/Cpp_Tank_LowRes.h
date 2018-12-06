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

	//Setter Functions for UE Blueprint
	UFUNCTION(BlueprintCallable, Category = "Tank")
		void SetTurrent(UChildActorComponent* Turrent);
	UFUNCTION(BlueprintCallable, Category = "Tank")
		void SetBarrel(UChildActorComponent* Barrel);
	UFUNCTION(BlueprintCallable, Category = "Tank")
		void SetBody(UChildActorComponent* Body);

private:
	//Variables to Hold Setter functions
	UChildActorComponent* Turrent = nullptr;
	UChildActorComponent* Barrel = nullptr;
	UChildActorComponent* Body = nullptr;

	//Movement Functions
	void RotateTurrent(float speed);
	void RotateBarrel(float speed);
	void MoveBody(float speed);
	void RotateBody(float speed);

	//Scale the Tank's movement and Rotation Amount.
	UPROPERTY(EditAnywhere, Category = "Tank")
	float MovementScale = 1500;
	UPROPERTY(EditAnywhere, Category = "Tank")
	float RotationScale = 100;
};