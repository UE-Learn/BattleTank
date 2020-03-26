// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
    Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
	FiringState = EFiringState::Reloading;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	double CurrentTime = FPlatformTime::Seconds();
	bool bReloaded = (CurrentTime - LastFireTime) > ReloadTimeInSeconds;
	if (bReloaded) 
	{
		if (IsBarrelMoving())
		{
			FiringState = EFiringState::Aiming;
		}
		else
		{
			FiringState = EFiringState::Locked;
		}
	}
	else
	{
		FiringState = EFiringState::Reloading;
	}
}

bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01f);
}

void UTankAimingComponent::AimAt(const FVector& TargetLocation)
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
			AimDirection = TossVelocity.GetSafeNormal();
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

void UTankAimingComponent::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("fire %s"), *GetOwner()->GetName());

	if (FiringState == EFiringState::Reloading) return;
	if (!ensure(Barrel) || !ensure(ProjectileBlueprint)) return;

	FVector TargetLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FRotator TargetRotation = Barrel->GetSocketRotation(FName("Projectile"));
	FActorSpawnParameters Parameters;
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, TargetLocation, TargetRotation);
	Projectile->Launch(LaunchSpeed);

	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::MoveBarrelTowards(const FVector& AimDirection)
{
	if (!Barrel || !Turret) return;
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;	

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}





