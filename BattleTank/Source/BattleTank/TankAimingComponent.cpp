// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.h"

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
		if (UGameplayStatics::SuggestProjectileVelocity(this, TossVelocity, BarrelLocation, TargetLocation, LaunchSpeed, 
				false, 0.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace)) {
			auto AimDirection = TossVelocity.GetSafeNormal();
			UE_LOG(LogTemp, Warning, TEXT("Tank %s aiming at %s"), *GetOwner()->GetName(), *AimDirection.ToString());
		}
	}

	FVector Direction = GetOwner()->GetActorLocation() - TargetLocation;
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UStaticMeshComponent* TurretToSet)
{
	Turret = TurretToSet;
}




