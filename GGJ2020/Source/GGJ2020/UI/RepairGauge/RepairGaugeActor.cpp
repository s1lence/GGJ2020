// Fill out your copyright notice in the Description page of Project Settings.


#include "RepairGaugeActor.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "Custom/Events/Events.h"
#include "Custom/Events/EventDispatcher.h"
#include "UI/RepairGauge/RepairGaugeWidget.h"

// Sets default values
ARepairGaugeActor::ARepairGaugeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; // #QUESTION Should it be so?

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

	auto playerData = static_cast<const PlayerRepairedObjectEventData&>(eventData);

	if (playerData.Id == 1)
	{
		Player1RepairProgress += playerData.AmountOfDetailsBringed;
		widget->SetFirstPlayerGaugePercents(FMath::Min(AmountOfDetailsNeeded, Player1RepairProgress) / AmountOfDetailsNeeded);

		GetWorld()->GetTimerManager().SetTimer(Player1TimerHandle, this, &ARepairGaugeActor::OnPlayer1TimePassed, TimeToReduceRepairProgress, true);

		if (Player1RepairProgress >= AmountOfDetailsNeeded)
		{
			if (BaseGameEvent* playerWonEvent = EventDispatcher::GetInstance().GetEvent(GameplayEventType::PlayerObjectFullyRepaired))
			{
				playerWonEvent->Broadcast(PlayerObjectFullyRepairedEventData(playerData.Id));

				GetWorld()->GetTimerManager().ClearTimer(Player1TimerHandle);
			}
		}
	}
	else if (playerData.Id == 2)
	{
		Player2RepairProgress += playerData.AmountOfDetailsBringed;
		widget->SetSecondPlayerGaugePercents(FMath::Min(AmountOfDetailsNeeded, Player2RepairProgress) / AmountOfDetailsNeeded);

		GetWorld()->GetTimerManager().SetTimer(Player2TimerHandle, this, &ARepairGaugeActor::OnPlayer2TimePassed, TimeToReduceRepairProgress, true);

		if (Player2RepairProgress >= AmountOfDetailsNeeded)
		{

			if (BaseGameEvent* playerWonEvent = EventDispatcher::GetInstance().GetEvent(GameplayEventType::PlayerObjectFullyRepaired))
			{
				playerWonEvent->Broadcast(PlayerObjectFullyRepairedEventData(playerData.Id));

				GetWorld()->GetTimerManager().ClearTimer(Player2TimerHandle);
			}
		}
	}
	else
	{
		check(false && "Player id is not 1 nor 2");
	}
}

void ARepairGaugeActor::OnPlayer1TimePassed()
{
	URepairGaugeWidget* widget = static_cast<URepairGaugeWidget*>(GaugeWidgetComponent->GetUserWidgetObject());
	if (!widget)
	{
		return;
	}

	if (Player1RepairProgress > 0.0f)
	{
		Player1RepairProgress--;
		widget->SetFirstPlayerGaugePercents(Player1RepairProgress / AmountOfDetailsNeeded);
	}
}

void ARepairGaugeActor::OnPlayer2TimePassed()
{
	URepairGaugeWidget* widget = static_cast<URepairGaugeWidget*>(GaugeWidgetComponent->GetUserWidgetObject());
	if (!widget)
	{
		return;
	}

	if (Player2RepairProgress > 0.0f)
	{
		Player2RepairProgress--;
		widget->SetSecondPlayerGaugePercents(Player2RepairProgress / AmountOfDetailsNeeded);
	}
}