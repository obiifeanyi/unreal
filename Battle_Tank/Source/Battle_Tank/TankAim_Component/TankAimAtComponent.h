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

	//Get Hit-location from the controller
	void TankAimAt(FVector HitLocation);

	//Called in BP to fire.
	UFUNCTION(BlueprintCallable, Category = "Tank")
		void Fire();

	//Gets the firing stated to pass to UI aim and used  AI to fire.
	UFUNCTION(BlueprintCallable)
		EFiringState GetFiringState () const;

protected:

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	//Initialization of Barrel and Turrent
	UFUNCTION(BlueprintCallable, Category = "SetUp")
		void Initialise(UTankBarrel* BarrelToSet, UTankTurrent* TurrentToSet);
	

	//Projectile for tank
	UPROPERTY(EditAnywhere, Category = "Tank")
		TSubclassOf<class AProjectile> BPProjectile;

	UPROPERTY(EditDefaultsOnly, Category = "Tank")
		float LauchSpeed = 10000;

	UPROPERTY(EditAnywhere,Category = "Firing")
		float FiringRate = 3;

private:

	//Set Direction Of Barrel
	void MoveBarrelTowards(FVector AimDirection);
	
	//Set Barrel and Turrent
	UTankBarrel* Barrel = nullptr;
	
	UTankTurrent* Turrent = nullptr;

	EFiringState FiringState = EFiringState::Aim;

	//If the tank can fire projectile based on timer.
	void SetCanFire(float RatePerSecond);

	//Can fire system
		bool bCanFire = false;
		bool JustFired = false;
		float Counter = 0;
		float OffsetTimer = 0;

		float LastReloadTime;
		bool IsBarrelMoving();
		FVector AimDirection;

};