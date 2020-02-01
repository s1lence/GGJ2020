// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RepairGaugeWidget.generated.h"

/**
 * 
 */

UCLASS()
class GGJ2020_API URepairGaugeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	URepairGaugeWidget(const FObjectInitializer& objectInitializer);
private:
	void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* ProgressBarPlayer1;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* ProgressBarPlayer2;
public:
	void ResetGauges();

	void SetFirstPlayerGaugePercents(float percents /*0-1*/);

	void SetSecondPlayerGaugePercents(float percents /*0-1*/);

private:
	//float AmountOfItemsRequired = 5.0f;

	//float FirstPlayerRepairProgress = 0.0f;
	//float SecondPlayerRepairProgress = 0.0f;
};


