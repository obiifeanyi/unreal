// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimAtComponent.generated.h"

class UTankBarrel;
class UTankTurrent;

UENUM()
enum class EFiringState : uint8
{
	Aim,
	Locked,
	Reloading
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLE_TANK_API UTankAimAtComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimAtComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//Tank Aiming Component
	void TankAimComp(FVector AimAt, float LauchSpeed);

protected:
	// Called when the game starts
		virtual void BeginPlay() override;
	//Initialization of Barrel and Turrent
		UFUNCTION(BlueprintCallable, Category = "SetUp")
		void Initialise(UTankBarrel* BarrelToSet, UTankTurrent* TurrentToSet);
	//Gets the firing stated to pass to UI aim
		UFUNCTION(BlueprintCallable)
			EFiringState GetFiringState () const;
private:
	//Set Direction Of Barrel
		void MoveBarrelTowards(FVector AimDirection);
	//Set Barrel and Turrent
	UTankBarrel* Barrel = nullptr;
	UTankTurrent* Turrent = nullptr;
	//
		EFiringState FiringState = EFiringState::Locked;
};