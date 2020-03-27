// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	if (CollisionMesh)
	{
    	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	}
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// if (!bExploded)
	{
		bExploded = true;
		if (LaunchBlast)
		{
			LaunchBlast->Deactivate();
		}
		if (ImpactBlast)
		{
			ImpactBlast->Activate();
			SetRootComponent(ImpactBlast);
		}
		if (ExplosionForce)
		{
			ExplosionForce->FireImpulse();
			UGameplayStatics::ApplyRadialDamage(
				this, 
				ProjectileDamage,
				GetActorLocation(),
				ExplosionForce->Radius,
				UDamageType::StaticClass(),
				TArray<AActor*>()
			);
		}
		if (CollisionMesh)
		{
			CollisionMesh->DestroyComponent();
		}
		FTimerHandle SomeHandle;
		GetWorld()->GetTimerManager().SetTimer(SomeHandle, this, &AProjectile::OnTimerExpire, DestroyDelay, false);
	}
}

void AProjectile::OnTimerExpire()
{
	Destroy();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AProjectile::Launch(float Speed)
{
	if (ProjectileMovement != nullptr)
	{
		// UE_LOG(LogTemp, Warning, TEXT("Launch!"));
		ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
		ProjectileMovement->Activate();
	}
}

