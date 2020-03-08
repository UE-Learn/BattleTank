// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATankPlayerController();

	ATank* GetControlledTank() const;

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

private:
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookDirection(FVector& LookDirection) const;

	UPROPERTY(EditAnywhere)
	float CrossHairLocationX = .5f;
	
	UPROPERTY(EditAnywhere)
	float CrossHairLocationY = .33f;
	
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;
	

};
