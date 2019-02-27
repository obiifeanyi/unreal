// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTracks.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API UTankTracks : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetThrottle(float speed);

private:

	//Constructor
	UTankTracks();

	//Begin Play
	virtual void BeginPlay() override;

	void SideWaysFriction();
	   
	float Throttle = 0;

protected:

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
	UPROPERTY(EditDefaultsOnly, Category = "SimonCustom")
		float MAXSPEED = 150000000.0;

	void DriveThrottle();
};
