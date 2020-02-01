// Fill out your copyright notice in the Description page of Project Settings.


#include "TilesManager.h"
#include "Tile.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATilesManager::ATilesManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void ATilesManager::BeginPlay()
{
	Super::BeginPlay();

    
    m_InactiveTiles.Reserve(30);
    for (int i = 0; i < 30; ++i)
    {
        int id = FMath::RandRange(0, 399);

        m_Tiles[id]->GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        m_Tiles[id]->GetMesh()->SetVisibility(false);
        m_InactiveTiles.Add(id);
    }
}

// Called every frame
void ATilesManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
