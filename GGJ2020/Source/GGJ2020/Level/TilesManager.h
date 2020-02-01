// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Custom/Events/Events.h"
#include "Custom/Events/EventsHandler.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FallingSpeed = 30.0f;


private:
	TArray<int> m_InactiveTiles;

	EventsHandler m_EventsHandler;

	void SubcribeOnEvents();
	void OnPlayerWonMatch(const EventData& eventData);

};
