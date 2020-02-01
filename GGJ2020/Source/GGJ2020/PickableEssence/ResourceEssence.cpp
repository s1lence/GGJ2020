// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceEssence.h"
#include "GGJ2020\Character\ResourceInventoryComponent.h"

void AResourceEssence::OnPicked(AActor* Picker)
{
	UResourceInventoryComponent* inventoryComponent = Cast<UResourceInventoryComponent, UActorComponent>(Picker->GetComponentByClass(UResourceInventoryComponent::StaticClass()));
	if (inventoryComponent->GetNumberOfResources() < inventoryComponent->GetMaxNumberOfResources())
	{
		inventoryComponent->IncrementNumberOfResources();
	}
}
