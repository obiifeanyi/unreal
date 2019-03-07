// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Gameframework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include <Particles/ParticleSystemComponent.h>
#include <Kismet/GameplayStatics.h>


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//create a projectile movement component.
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement"); 
	ProjectileMovement->bAutoActivate = false;
	ProjectileMovement->bShouldBounce = 0;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Projectile Ball"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(true);

	PrtProjectileTrail = CreateDefaultSubobject<UParticleSystemComponent>(FName("Projectile Explosion"));
	PrtProjectileTrail->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);

	//Explosion on hit Particle System Set up
	PrtHitExplosion = CreateDefaultSubobject<UParticleSystemComponent>(FName("Hit Explosion"));
	PrtHitExplosion->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	PrtHitExplosion->bAutoActivate = false;

	//RadialForce to Push Objects Away.
	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ExplosionForce->bAutoActivate = false;
	ExplosionForce->ImpulseStrength = 300.0f;
	ExplosionForce->ForceStrength = 15000000.0f;
	ExplosionForce->Radius = ShockWaveRadius;
	//TODo code in radius of force.
	

}


void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	PrtHitExplosion->Activate();
	PrtProjectileTrail->Deactivate();
	ExplosionForce->Activate();
	ExplosionForce->FireImpulse();
	CollisionMesh->DestroyComponent();
	SetRootComponent(PrtHitExplosion);
	
	//Damage the Actor In Range
	UGameplayStatics::ApplyRadialDamageWithFalloff(
		this,
		BaseDamage,
		MinimuDamage,
		GetActorLocation(),
		1.0f,
		ShockWaveRadius,
		ExpDamageForce,
		UDamageType::StaticClass(),
		TArray<AActor*>()
	);

	//Trigger death of Actor
	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer,this,&AProjectile::KillActor, LifeSpawnAfterCollision);


}

void AProjectile::KillActor()
{
	Destroy();
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionMesh->OnComponentHit.AddDynamic(this,&AProjectile::OnHit);
	
}

void AProjectile::LaunchProjectile(float speed)
{
	if (!ProjectileMovement)return;
	
	ProjectileMovement->SetVelocityInLocalSpace(FVector(FVector::ForwardVector * speed));
	ProjectileMovement->Activate();
	
}