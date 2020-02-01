// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ResourceInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GGJ2020_API UResourceInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UResourceInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void IncrementNumberOfResources();

	int GetNumberOfResources() const { return NumberOfResources; }
	int GetMaxNumberOfResources() const { return MaxNumberOfResources; }


protected:
	UPROPERTY(BlueprintReadWrite)
	int MaxNumberOfResources = 3;

	UPROPERTY(BlueprintReadWrite)
	int NumberOfResources = 0;
};
