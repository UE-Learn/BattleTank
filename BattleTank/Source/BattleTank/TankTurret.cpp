// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
    auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawNewRotation = RelativeRotation.Yaw + RotationChange; 
    auto Rotation = RawNewRotation; //TODO add 360
    SetRelativeRotation(FRotator(0, Rotation, 0));

    float Time = GetWorld()->GetTimeSeconds();
    // UE_LOG(LogTemp, Warning, TEXT("Rotate %f -> %f"), RawNewRotation, Rotation);
}

