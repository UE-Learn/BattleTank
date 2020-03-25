// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
class AACtor;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "Call AI Move To from BP"))
	void BPMoveToLocation(FVector TargetLocation);

	UFUNCTION(BlueprintCallable, Category = Ddd)
	void SomeFunc(FVector TargetLocation);

private:
	void AimTowardsPlayer();

	ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;
};
