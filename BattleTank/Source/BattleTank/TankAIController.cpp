// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    auto Tank = GetPawn();
    if (ensure(Tank))
    {
        AimingComponent = Tank->FindComponentByClass<UTankAimingComponent>();
    }
}

APawn* ATankAIController::GetPlayerTank() const
{
    if (auto PlayerController = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController()))
    {
        return PlayerController->GetControlledTank();
    }

    return nullptr;
}


void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AimTowardsPlayer();
}


void ATankAIController::AimTowardsPlayer()
{
    auto Player = GetPlayerTank();
    if (Player)
    {
        if (AimingComponent)
        {
            AimingComponent->AimAt(Player->GetActorLocation());

            if (AimingComponent->GetFiringState() == EFiringState::Locked)
            {
                AimingComponent->Fire();
            }
            
            // MoveToActor(Player, 4000.f);
            BPMoveToLocation(Player->GetActorLocation());
        }
    }
}

void ATankAIController::SomeFunc(FVector TargetLocation)
{
    UE_LOG(LogTemp, Warning, TEXT("sdfs"));
    // MoveToLocation(FVector(0.f));
    auto Player = GetPlayerTank();
    if (Player)
    {
        auto Tank = GetPawn();
        if (Tank)
        {
            // Tank->AimAt(Player->GetActorLocation());
            //Tank->Fire();
            UE_LOG(LogTemp, Warning, TEXT("2323"));
            // MoveToActor(Player, 4000.f);
            BPMoveToLocation(TargetLocation);
        }
    }
}