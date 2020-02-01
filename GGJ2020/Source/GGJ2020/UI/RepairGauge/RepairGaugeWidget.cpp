// Fill out your copyright notice in the Description page of Project Settings.


#include "RepairGaugeWidget.h"
#include "Components/ProgressBar.h"

URepairGaugeWidget::URepairGaugeWidget(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{}

void URepairGaugeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AddToViewport();
}

void URepairGaugeWidget::ResetGauges()
{
	ProgressBarPlayer1->Percent = 0.0f;
	ProgressBarPlayer2->Percent = 0.0f;
}

void URepairGaugeWidget::SetFirstPlayerGaugePercents(float percents)
{
	ProgressBarPlayer1->Percent = percents;
}

void URepairGaugeWidget::SetSecondPlayerGaugePercents(float percents)
{
	ProgressBarPlayer2->Percent = percents;
}