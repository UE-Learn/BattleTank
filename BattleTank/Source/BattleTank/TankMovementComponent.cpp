// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
    UE_LOG(LogTemp, Warning, TEXT("Init"));
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
    if (LeftTrack && RightTrack)
    {
        LeftTrack->SetThrottle(Throw);
        RightTrack->SetThrottle(Throw);
    }
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
    if (LeftTrack && RightTrack)
    {
        LeftTrack->SetThrottle(Throw);
        RightTrack->SetThrottle(-Throw);
    }
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
    auto TankForward = GetOwner()->GetActorForwardVector();
    auto Direction = MoveVelocity.GetSafeNormal();
    UE_LOG(LogTemp, Warning, TEXT("MOVE %s"), *Direction.ToString());

    float ForwardThrow = FVector::DotProduct(TankForward, Direction);
    IntendMoveForward(ForwardThrow);

    FVector CrossProduct = FVector::CrossProduct(TankForward, Direction);
    IntendTurnRight(CrossProduct.Z);
}