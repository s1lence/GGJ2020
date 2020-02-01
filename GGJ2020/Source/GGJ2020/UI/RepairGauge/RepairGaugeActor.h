// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Custom/Events/EventsHandler.h"
#include "Custom/Events/Events.h"
#include "RepairGaugeActor.generated.h"

UCLASS()
class GGJ2020_API ARepairGaugeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARepairGaugeActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GaugeWidget")
	class UWidgetComponent* GaugeWidgetComponent;

private:
	void SubcribeOnEvents();

	void OnPlayerRepairedObject(const EventData& eventData);
private:
	EventsHandler m_EventsHandler;

	float Player1RepairProgress = 0.0f;
	float Player2RepairProgress = 0.0f;

	int AmountOfDetailsNeeded = 5;
};
