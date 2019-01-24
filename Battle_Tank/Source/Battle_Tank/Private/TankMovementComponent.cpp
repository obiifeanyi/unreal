// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTracks.h"

void UTankMovementComponent::IntendedMovementForward(float Throw)
{
	//UE_LOG(LogTemp, Warning, TEXT("Moving Front %f"), Throw);
	if (!LeftTrack || !RightTrack)return; //If not set in BP exit
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendedMovementTurnRight(float Throw)
{
	//UE_LOG(LogTemp, Warning, TEXT("Moving Front %f"), Throw);
	if (!LeftTrack || !RightTrack)return; //If not set in BP exit
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::Initialzier(UTankTracks* LeftTrack, UTankTracks* RightTrack)
{
	if(!LeftTrack || !RightTrack)return;
	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}


