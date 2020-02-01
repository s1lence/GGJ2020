// Fill out your copyright notice in the Description page of Project Settings.


#include "InputHandler.h"
#include "Character/GameCharacter.h"
#include "Kismet/GameplayStatics.h"

#define GET_ACTION_NAME_STARTED(NAME) NAME##Pressed
#define GET_ACTION_NAME_ENDED(NAME) NAME##Released

#define GET_TEXT(NAME) TEXT(#NAME)

#define BIND_ACTION_PRESS(NAME, HANDLER_CLASS_NAME) \
	PlayerInputComponent->BindAction(GET_TEXT(NAME), IE_Pressed, this, &HANDLER_CLASS_NAME::GET_ACTION_NAME_STARTED(NAME))

#define BIND_ACTION_RELEASE(NAME, HANDLER_CLASS_NAME) \
	PlayerInputComponent->BindAction(GET_TEXT(NAME), IE_Released, this, &HANDLER_CLASS_NAME::GET_ACTION_NAME_ENDED(NAME))

#define BIND_FULL_PRESS_ACTION(NAME, HANDLER_CLASS_NAME)	\
	BIND_ACTION_PRESS(NAME, HANDLER_CLASS_NAME);			\
	BIND_ACTION_RELEASE(NAME, HANDLER_CLASS_NAME)

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
		m_Player1->SetId(1);
	    m_Player2 = Cast<AGameCharacter>(FoundCharacters[1]);
		m_Player2->SetId(2);
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

void AInputHandler::ShootPlayer1Pressed()
{
    if (m_Player1)
    {
        m_Player1->ShootActionPressed();
    }
}

void AInputHandler::ShootPlayer1Released()
{
    if (m_Player1)
    {
        m_Player1->ShootActionReleased();
    }
}

void AInputHandler::ShootPlayer2Pressed()
{
    if (m_Player2)
    {
        m_Player2->ShootActionPressed();
    }
}

void AInputHandler::ShootPlayer2Released()
{
    if (m_Player2)
    {
        m_Player2->ShootActionReleased();
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

    BIND_FULL_PRESS_ACTION(ShootPlayer1, AInputHandler);
    BIND_FULL_PRESS_ACTION(ShootPlayer2, AInputHandler);
}

