// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Is used to set maximum drivig force, and apply forces to the tank
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//sets throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category=Input)
	void SetThrottle(float Throttle);

	// max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000.f; // 40 tonne tank, 1g acceleration
};
