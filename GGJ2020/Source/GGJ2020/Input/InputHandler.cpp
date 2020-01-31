// Fill out your copyright notice in the Description page of Project Settings.


#include "InputHandler.h"
#include "Character/GameCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AInputHandler::AInputHandler()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInputHandler::BeginPlay()
{
	Super::BeginPlay();

    TArray<AActor*> FoundCharacters;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGameCharacter::StaticClass(), FoundCharacters);
    if (FoundCharacters.Num() == 2)
    {
	    m_Player1 = Cast<AGameCharacter>(FoundCharacters[0]);
	    m_Player2 = Cast<AGameCharacter>(FoundCharacters[1]);
    }
}

// Called every frame
void AInputHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInputHandler::MoveForwardPlayer1(float value)
{
    if (value != 0.f && m_Player1)
    {
        m_Player1->MoveForward(value);
    }
}

void AInputHandler::MoveRightPlayer1(float value)
{
    if (value != 0.f && m_Player1)
    {
        m_Player1->MoveRight(value);
    }
}

void AInputHandler::MoveForwardPlayer2(float value)
{
    if (value != 0.f && m_Player2)
    {
        m_Player2->MoveForward(value);
    }
}

void AInputHandler::MoveRightPlayer2(float value)
{
    if (value != 0.f && m_Player2)
    {
        m_Player2->MoveRight(value);
    }
}


// Called to bind functionality to input
void AInputHandler::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForwardPlayer1", this, &AInputHandler::MoveForwardPlayer1);
	PlayerInputComponent->BindAxis("MoveRightPlayer1", this, &AInputHandler::MoveRightPlayer1);

    PlayerInputComponent->BindAxis("MoveForwardPlayer2", this, &AInputHandler::MoveForwardPlayer2);
    PlayerInputComponent->BindAxis("MoveRightPlayer2", this, &AInputHandler::MoveRightPlayer2);
}

