// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class GGJ2020_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetMoveDirection(const FVector& direction);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	class UStaticMeshComponent *MeshBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector moveDirection{ 1.f, 0.f, 0.f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float moveSpeed = 10.f;

};
