// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HR_Tank.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegatDeath);

class AProjectile;

UCLASS()
class BATTLE_TANK_API AHR_Tank : public APawn
{
	GENERATED_BODY()


private:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)override;
	
		
public:



	FDelegatDeath TankDeath; //TODO Can i put in private.

protected:
	
	// Sets default values for this pawn's properties
	AHR_Tank();
	//
	virtual void BeginPlay() override;

	//Get the Health to be used by UMG
	UFUNCTION(BlueprintPure,Category = "Life")
		float GetTankHealth() const;

	UPROPERTY(EditDefaultsOnly,Category = "Life")
		int32 PlayerHealth= 100;

	int32 CurrentHealth = 0;
};