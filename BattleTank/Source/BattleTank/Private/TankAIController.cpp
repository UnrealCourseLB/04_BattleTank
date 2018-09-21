// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	APawn* AIControlledTank = GetPawn();
	APawn* PlayerControlledTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(PlayerControlledTank && AIControlledTank)) { return; }
	
	//Move towards the player
	MoveToActor(PlayerControlledTank, AcceptanceRadius);

	//Aim Towards the player
	UTankAimingComponent* AimingComponent = AIControlledTank->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent)) { return; }
		
	AimingComponent->AimAt(PlayerControlledTank->GetActorLocation());
	
	if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked)
	{
		AimingComponent->Fire(); //TODO don't fire every frame
	}
	
}

