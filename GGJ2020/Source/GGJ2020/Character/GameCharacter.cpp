// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "GameCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "Components/ArrowComponent.h"
#include "Projectile.h"

#define BIND_AXIS(NAME, HANDLER_CLASS_NAME) \
	PlayerInputComponent->BindAxis(TEXT(#NAME), this, &HANDLER_CLASS_NAME::NAME)

#define GET_ACTION_NAME_STARTED(NAME) NAME##Pressed
#define GET_ACTION_NAME_ENDED(NAME) NAME##Released

#define GET_TEXT(NAME) TEXT(#NAME)

#define BIND_ACTION_PRESS(NAME, HANDLER_CLASS_NAME) \
	PlayerInputComponent->BindAction(GET_TEXT(NAME), IE_Pressed, this, &HANDLER_CLASS_NAME::GET_ACTION_NAME_STARTED(NAME))

#define BIND_ACTION_RELEASE(NAME, HANDLER_CLASS_NAME) \
	PlayerInputComponent->BindAction(GET_TEXT(NAME), IE_Released, this, &HANDLER_CLASS_NAME::GET_ACTION_NAME_ENDED(NAME))

#define BIND_FULL_PRESS_ACTION(NAME, HANDLER_CLASS_NAME)	\
	BIND_ACTION_PRESS(NAME, HANDLER_CLASS_NAME);			\
	BIND_ACTION_RELEASE(NAME, HANDLER_CLASS_NAME)


#define MY_LOG(FORMAT, ...) \
	UE_LOG(LogTemp, Warning, TEXT(FORMAT), __VA_ARGS__)

#ifdef SHOOTING_DEBUG_LOG_ENABLED
#define SHOOTING_DEBUG_LOG(FORMAT, ...) MY_LOG(FORMAT, __VA_ARGS__)
#else
#define SHOOTING_DEBUG_LOG(FORMAT, ...) void
#endif // SHOOTING_DEBUG_LOG_ENABLED


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
}

void AGameCharacter::MoveForward(float Value)
{
	const FVector Direction(Value, 0.0f, 0.0f);
	AddMovementInput(Direction, 1.0f);
}

void AGameCharacter::MoveRight(float Value)
{
	const FVector Direction(0.0f, Value, 0.0f);
	// add movement in that direction
	AddMovementInput(Direction, 1.0f);
}

void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateShooting(DeltaTime);
}

void AGameCharacter::ShootActionPressed()
{
	m_shooting = true;
}

void AGameCharacter::ShootActionReleased()
{
	m_shooting = false;
}

void AGameCharacter::UpdateShooting(float DeltaTime)
{
	m_timeElapsed += DeltaTime;

	if (!m_shooting || m_timeElapsed <= ShootCooldown)
	{
		return;
	}

	if (m_currentClipSize > 0)
	{
		SHOOTING_DEBUG_LOG("Ammo in clip: %d/%d", m_currentClipSize, MaxClipSize);

		Shoot();
		m_timeElapsed = 0.0f;
		m_currentClipSize--;

		SHOOTING_DEBUG_LOG("Ammo in clip: %d/%d", m_currentClipSize, MaxClipSize);
	}
	else /* no ammo in clip	*/
	{
		if (m_timeElapsed > ReloadTime)
		{
			m_timeElapsed = 0.0f;
			m_currentClipSize = MaxClipSize;
		}

		SHOOTING_DEBUG_LOG("Reloading... %2.2f/%2.2f", m_timeElapsed, ReloadTime);
	}
}

void AGameCharacter::Shoot()																										
{												
	UWorld *world = GetWorld();
	FVector const AimDirection = GetCapsuleComponent()->GetForwardVector();
	FVector const spawnLocation = GetCapsuleComponent()->GetComponentLocation() + AimDirection * ProjectileSpawnDistanceMultiplier;

	AProjectile *tmp = world->SpawnActor<AProjectile>(spawnLocation, GetCapsuleComponent()->GetComponentRotation());
	tmp->AddForce(ForceAppliedToProjectile * AimDirection);
	tmp->SetActorScale3D(FVector(ProjectileScaleCoefficient));
}
