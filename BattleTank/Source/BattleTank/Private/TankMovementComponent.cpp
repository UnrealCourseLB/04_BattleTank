// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	//no need to use inherited behaviour
	FString TankName = GetOwner()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s tank move velocity: %s"),*TankName, *MoveVelocity.ToString());
	FVector AIFowardIntention = MoveVelocity.GetSafeNormal();
	FVector TankFoward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	float ForwardThrow = FVector::DotProduct(AIFowardIntention, TankFoward);
	FVector RightThrowVector = FVector::CrossProduct(TankFoward, AIFowardIntention);
	float RightThrow = RightThrowVector.Z;

	IntendMoveForward(ForwardThrow);
	IntendMoveRight(RightThrow);
}


void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack))
	{
		return;
	}

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	//TODO clamp speed so that it is not doubled by using other input sources
}

void UTankMovementComponent::IntendMoveRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack))
	{
		return;
	}

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	//TODO clamp speed so that it is not doubled by using other input sources
}

