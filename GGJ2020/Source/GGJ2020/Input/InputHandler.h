// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputHandler.generated.h"

class AGameCharacter;

UCLASS()
class GGJ2020_API AInputHandler : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AInputHandler();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForwardPlayer1(float value);
	void MoveRightPlayer1(float value);

    void MoveForwardPlayer2(float value);
    void MoveRightPlayer2(float value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY()
	AGameCharacter* m_Player1 = nullptr;
	AGameCharacter* m_Player2 = nullptr;
};
