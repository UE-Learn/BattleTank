// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "Components/PrimitiveComponent.h"

void UTankTrack::SetThrottle(float Throttle)
{
    Throttle = FMath::Clamp<float>(Throttle, -1.f, 1.f);

    auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    if (TankRoot)
    {
        TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
    }
}