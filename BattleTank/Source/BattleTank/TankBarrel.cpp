// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/World.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
    FMath::Clamp(RelativeSpeed, -1.0f, +1.0f);
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
    auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawNewElevation = RelativeRotation.Pitch + ElevationChange; 
    auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
    SetRelativeRotation(FRotator(Elevation, 0, 0));

    float Time = GetWorld()->GetTimeSeconds();
    // UE_LOG(LogTemp, Warning, TEXT("Elevate %f -> %f"), RawNewElevation, Elevation);
}