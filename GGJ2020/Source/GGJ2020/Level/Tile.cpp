// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATile::ATile()
{
	PrimaryActorTick.bCanEverTick = false;
    ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Cube"));
    if (MeshAsset.Succeeded())
    {
        m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMesh"));
        m_Mesh->SetStaticMesh(MeshAsset.Object);
    }

    RootComponent = m_Mesh;
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

