// Fill out your copyright notice in the Description page of Project Settings.


#include "PickerComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GGJ2020/Pickable/PickableBase.h"

// Sets default values for this component's properties
UPickerComponent::UPickerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPickerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UCapsuleComponent* capsuleComponent = Cast<ACharacter>(GetOwner())->GetCapsuleComponent();
	capsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &UPickerComponent::PickEssence);
}


// Called every frame
void UPickerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPickerComponent::PickEssence(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APickableBase* pickable = Cast<APickableBase>(OtherActor);
	if (pickable != nullptr)
	{
		APickableEssenceBase* pickableEssence = pickable->GetPickableEssence();
		if (pickableEssence != nullptr)
		{
			pickableEssence->OnPicked(GetOwner());
		}
	}
}
