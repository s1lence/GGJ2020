// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickableEssence/PickableEssenceBase.h"
#include "ResourceEssence.generated.h"

/**
 * 
 */
UCLASS()
class GGJ2020_API AResourceEssence : public APickableEssenceBase
{
	GENERATED_BODY()
	
public:

	void OnPicked(AActor* Picker) override;
};
