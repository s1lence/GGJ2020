// Fill out your copyright notice in the Description page of Project Settings.


#include "RepairGaugeActor.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"

// Sets default values
ARepairGaugeActor::ARepairGaugeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // #QUESTION Should it be so?

	GaugeWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("GaugeWidget"));
	ConstructorHelpers::FClassFinder<UUserWidget> widget(TEXT("/Game/RepairGaugeWidgetBP"));

	if (widget.Succeeded())
	{
		GaugeWidget->SetWidgetClass(widget.Class);
	}
}

// Called when the game starts or when spawned
void ARepairGaugeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARepairGaugeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

