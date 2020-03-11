// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void ATank::AimAt(const FVector& TargetLocation)
{
	if (AimingComponent)
	{
		AimingComponent->AimAt(TargetLocation, LaunchSpeed);
	}
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
	if (AimingComponent)
	{
		AimingComponent->SetBarrelReference(BarrelToSet);
	}
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	if (AimingComponent)
	{
		AimingComponent->SetTurretReference(TurretToSet);
	}
}

void ATank::Fire()
{
	if (!Barrel || !ProjectileBlueprint) return;
	FVector TargetLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FRotator TargetRotation = Barrel->GetSocketRotation(FName("Projectile"));
	FActorSpawnParameters Parameters;
	GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, TargetLocation, TargetRotation);
	UE_LOG(LogTemp, Warning, TEXT("Fire!"));
}

