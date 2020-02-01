// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
ABasicCharacter::ABasicCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    m_Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    m_Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));

    RootComponent = m_Mesh;
    FAttachmentTransformRules rules(EAttachmentRule::KeepRelative, false);
    m_Box->AttachToComponent(RootComponent, rules);
    m_Arrow->AttachToComponent(RootComponent, rules);

    m_Mesh->SetSimulatePhysics(true);
    m_Mesh->BodyInstance.bLockXRotation = true;
    m_Mesh->BodyInstance.bLockYRotation = true;
}

// Called when the game starts or when spawned
void ABasicCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasicCharacter::Shoot()
{
    OnShoot();
}

void ABasicCharacter::MoveForward(float Value)
{
    const FVector& currentLocation = m_Mesh->GetComponentLocation();
    const FVector newLocation(currentLocation + FVector(Value * 10.0f, 0.0f, 0.0f));
    m_Mesh->SetWorldLocation(newLocation);
}

void ABasicCharacter::MoveRight(float Value)
{
    const FVector& currentLocation = m_Mesh->GetComponentLocation();
    const FVector newLocation(currentLocation + FVector(0.0f, Value * 10.0f, 0.0f));
    m_Mesh->SetWorldLocation(newLocation);
}

// Called every frame
void ABasicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

