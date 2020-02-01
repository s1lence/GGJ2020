// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TilesManager.generated.h"

class ATile;

UCLASS()
class GGJ2020_API ATilesManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATilesManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadWrite)
	TArray<ATile*> m_Tiles;

private:
	UFUNCTION()
	void OnTimerElapsed();

private:
	FTimerHandle m_Timer;

	TArray<int> m_FallenTilesPositions;
};
