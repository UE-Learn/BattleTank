// Fill out your copyright notice in the Description page of Project Settings.


#include "TestNavMovementComponent.h"

 void UTestNavMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
 {
     UE_LOG(LogTemp, Warning, TEXT("qqqqq"));
     Super::RequestDirectMove(MoveVelocity, bForceMaxSpeed);

     auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
     if (TankRoot)
     {
        auto ForceApplied = TankRoot->GetForwardVector() * 2000.f;
        auto ForceLocation = TankRoot->GetComponentLocation();
        TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
     }
 }