// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameCharacter.generated.h"

UCLASS()
class AGameCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	AGameCharacter();

    void MoveForward(float Value);
    void MoveRight(float Value);


	int GetId() const { return Id; };
	void SetId(int id) { Id = id; };

	void ShootActionPressed();
	void ShootActionReleased();

	int TakeDetailsFromPlayersToObject();

	virtual void Tick(float DeltaTime) override;

protected:
	
	void Shoot();
	void UpdateShooting(float DeltaTime);

	float ProjectileSpawnDistanceMultiplier = 50.0f;

	float ShootCooldown = 0.08f;
	float ReloadTime = 3.5f;

	int MaxClipSize = 30;
	int m_currentClipSize = MaxClipSize;

	float ForceAppliedToProjectile = 800000.0f;
	float ProjectileScaleCoefficient = 0.12f;

	float m_timeElapsed = 0.0f;
	bool m_shooting = false;

private:
	int Id = 0; // #TODO Generate ID
};

