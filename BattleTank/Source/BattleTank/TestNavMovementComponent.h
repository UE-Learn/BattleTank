// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TestNavMovementComponent.generated.h"

/**
 * Test handling movement for navmesh
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTestNavMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
};
