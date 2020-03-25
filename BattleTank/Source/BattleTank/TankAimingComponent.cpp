// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(const FVector& TargetLocation, float LaunchSpeed)
{
	if (Barrel)
	{
		FVector BarrelLocation = Barrel->GetSocketLocation(FName("Projectile"));
    	// UE_LOG(LogTemp, Warning, TEXT("Tank %s aiming from %s to %s"), *GetOwner()->GetName(), *BarrelLocation.ToString(), *TargetLocation.ToString());

		FVector TossVelocity;
		bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(Barrel, TossVelocity, BarrelLocation, TargetLocation, LaunchSpeed, 
				false, 0.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace);
		if (bHaveAimSolution)
		{
			auto AimDirection = TossVelocity.GetSafeNormal();
			MoveBarrelTowards(AimDirection);
			// UE_LOG(LogTemp, Warning, TEXT("Tank %s aiming at %s"), *GetOwner()->GetName(), *AimDirection.ToString());
		}
		else
		{
			// UE_LOG(LogTemp, Warning, TEXT("no solution"));
		}
	}

	FVector Direction = GetOwner()->GetActorLocation() - TargetLocation;
}

void UTankAimingComponent::MoveBarrelTowards(const FVector& AimDirection)
{
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;	

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}




