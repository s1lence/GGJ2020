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

	int TakeDetailsFromPlayersToObject();

	virtual void Tick(float DeltaTime) override;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* MyComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
protected:
	
	void Shoot();

	float ProjectileSpawnDistanceMultiplier = 50.0f;

	float ForceAppliedToProjectile = 800000.0f;
	float ProjectileScaleCoefficient = 0.3f;

	UFUNCTION()
	void ResetCooldown();

private:
	int Id = 0; // #TODO Generate ID

	bool m_IsCooldown = false;
};

