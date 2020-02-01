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


AGameCharacter::AGameCharacter()
{
	m_Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("GunArrow"));
	FAttachmentTransformRules rules(EAttachmentRule::KeepRelative, false);
	m_Arrow->AttachToComponent(GetCapsuleComponent(), rules);
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