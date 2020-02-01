// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GGJ2020/PickableEssence/PickableEssenceBase.h"
#include "PickableBase.generated.h"

UCLASS()
class GGJ2020_API APickableBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickableBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	APickableEssenceBase* GetPickableEssence() const { return PickableEssence; }

protected:
	UPROPERTY(BlueprintReadWrite)
	APickableEssenceBase* PickableEssence = nullptr;
};
