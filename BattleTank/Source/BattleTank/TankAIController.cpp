// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    auto Tank = GetControlledTank();
    if (Tank)
    {
        UE_LOG(LogTemp, Warning, TEXT("Tank AI Controller controls tank: %s"), *Tank->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Tank AI Controller controls no tank"));
    }
    auto PlayerTank = GetPlayerTank();
    if (!PlayerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("Tank AI Controller could not find player tank"));
    }
}

ATank* ATankAIController::GetControlledTank() const
{
    // return nullptr;
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
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
        auto Tank = GetControlledTank();
        if (Tank)
        {
            // Tank->AimAt(Player->GetActorLocation());
        }
    }
}