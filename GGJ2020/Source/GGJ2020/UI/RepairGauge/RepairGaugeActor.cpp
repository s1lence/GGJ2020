// Fill out your copyright notice in the Description page of Project Settings.


#include "RepairGaugeActor.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "Custom/Events/Events.h"
#include "UI/RepairGauge/RepairGaugeWidget.h"

// Sets default values
ARepairGaugeActor::ARepairGaugeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // #QUESTION Should it be so?

	GaugeWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("GaugeWidget"));
	ConstructorHelpers::FClassFinder<UUserWidget> widget(TEXT("/Game/RepairGaugeWidgetBP"));

	if (widget.Succeeded())
	{
		GaugeWidgetComponent->SetWidgetClass(widget.Class);
	}
}

// Called when the game starts or when spawned
void ARepairGaugeActor::BeginPlay()
{
	Super::BeginPlay();
	
	SubcribeOnEvents();
}

// Called every frame
void ARepairGaugeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARepairGaugeActor::SubcribeOnEvents()
{
	m_EventsHandler.subscribe({
		{GameplayEventType::PlayerRepairedObject, [this](const EventData& eventData) { OnPlayerRepairedObject(eventData); }},
		});
}

void ARepairGaugeActor::OnPlayerRepairedObject(const EventData& eventData)
{
	if (eventData.eventType != GameplayEventType::PlayerRepairedObject)
	{
		return;
	}

	URepairGaugeWidget* widget = static_cast<URepairGaugeWidget*>(GaugeWidgetComponent->GetUserWidgetObject());
	if (!widget)
	{
		return;
	}

	auto data = static_cast<const PlayerRepairedObjectEventData&>(eventData);

	if (data.Id == 1)
	{
		if (Player1RepairProgress < AmountOfDetailsNeeded)
		{
			Player1RepairProgress += data.AmountOfDetailsBringed;
			widget->SetFirstPlayerGaugePercents(Player1RepairProgress / AmountOfDetailsNeeded);
		}
	}
	else if (data.Id == 2)
	{
		if (Player2RepairProgress < AmountOfDetailsNeeded)
		{
			Player2RepairProgress += data.AmountOfDetailsBringed;
			widget->SetSecondPlayerGaugePercents(Player2RepairProgress / AmountOfDetailsNeeded);
		}
	}
	else
	{
		check(false && "Player id is not 1 nor 2");
	}
}

