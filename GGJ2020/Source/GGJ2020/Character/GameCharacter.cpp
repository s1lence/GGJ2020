// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "GameCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ArrowComponent.h"
#include "Projectile.h"


AGameCharacter::AGameCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AGameCharacter::OnHit);
}

 void AGameCharacter::OnHit(UPrimitiveComponent* MyComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
 {
 	if (AProjectile* projectile = Cast<AProjectile>(OtherActor))
 	{
		SetActorLocation(GetActorLocation() + (-NormalImpulse.GetSafeNormal()) * 50.0f);
		projectile->Destroy();
 	}
 }

void AGameCharacter::MoveForward(float Value)
{
	const FVector Direction(Value, 0.0f, 0.0f);
	AddMovementInput(Direction, 5.0f);
}

void AGameCharacter::MoveRight(float Value)
{
	const FVector Direction(0.0f, Value, 0.0f);
	// add movement in that direction
	AddMovementInput(Direction, 5.0f);

}

void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameCharacter::ShootActionPressed()
{
	if (!m_IsCooldown)
	{
		Shoot();
		m_IsCooldown = true;
	}

	FTimerHandle timer;
	GetWorld()->GetTimerManager().SetTimer(timer, this, &AGameCharacter::ResetCooldown, 1.0f, false);
}

int AGameCharacter::TakeDetailsFromPlayersToObject()
{
	return 1; // #TODO pop all items from resources inventory
}

void AGameCharacter::ResetCooldown()
{
	m_IsCooldown = false;
}

void AGameCharacter::Shoot()																										
{												
	UWorld *world = GetWorld();
	FVector const AimDirection = GetCapsuleComponent()->GetForwardVector();
	FVector const spawnLocation = GetCapsuleComponent()->GetComponentLocation() + AimDirection * ProjectileSpawnDistanceMultiplier;

	AProjectile* bullet = GetWorld()->SpawnActor<AProjectile>(spawnLocation, GetCapsuleComponent()->GetComponentRotation());
	bullet->AddForce(ForceAppliedToProjectile * AimDirection);
	bullet->SetActorScale3D(FVector(ProjectileScaleCoefficient));
}
