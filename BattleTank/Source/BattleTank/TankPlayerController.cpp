// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Engine/World.h"
#include "TankPlayerController.h"

ATankPlayerController::ATankPlayerController()
{
    PrimaryActorTick.bCanEverTick = true;
}

ATank* ATankPlayerController::GetControlledTank() const
{
    // return nullptr;
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    auto Tank = GetControlledTank();
    if (Tank)
    {
        UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller controls tank: %s"), *Tank->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Tank Player Controller controls no tank"));
    }
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
    // UE_LOG(LogTemp, Warning, TEXT("Player controller tick"));
}


void ATankPlayerController::AimTowardsCrosshair()
{
    auto Tank = GetControlledTank();
    if (!Tank) return;
    
    FVector HitLocation;
    if (GetSightRayHitLocation(HitLocation))
    {
        Tank->AimAt(HitLocation);
    }
}

bool ATankPlayerController::GetLookDirection(FVector& LookDirection) const
{
    int32 ViewPortSizeX, ViewPortSizeY;
    GetViewportSize(ViewPortSizeX, ViewPortSizeY);
    FVector2D ScreenLocation(ViewPortSizeX * CrossHairLocationX, ViewPortSizeY * CrossHairLocationY);
    
    FVector WorldLocation;
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.X, WorldLocation, LookDirection);
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
    FVector LookDirection;
    if (GetLookDirection(LookDirection))
    {
        FHitResult HitResult;
        FVector Start = PlayerCameraManager->GetCameraLocation();
        FVector End = Start + LookDirection * LineTraceRange;
        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(GetControlledTank());
        if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, CollisionParams))
        {
            AActor* HitActor = HitResult.GetActor();
            if (HitActor)
            {
                // UE_LOG(LogTemp, Warning, TEXT("aiming actor %s"), *HitActor->GetName());
                HitLocation = HitResult.Location;
                return true;
            }
        }
    }
    HitLocation = FVector(0.f);
    return false;
}