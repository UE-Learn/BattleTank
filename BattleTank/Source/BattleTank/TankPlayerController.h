// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;
class ATank;
/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATankPlayerController();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookDirection(FVector& LookDirection) const;

	UTankAimingComponent* AimingComponent = nullptr;

	UPROPERTY(EditAnywhere)
	float CrossHairLocationX = .5f;
	
	UPROPERTY(EditAnywhere)
	float CrossHairLocationY = .33f;
	
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;
	

};
