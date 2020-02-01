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
	GetWorld()->GetTimerManager().SetTimer(m_Timer, this, &ATilesManager::OnTimerElapsed, 5.0f, true);
}

// Called every frame
void ATilesManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATilesManager::OnTimerElapsed()
{
	if (m_FallenTilesPositions.Num() > 0)
	{
		for (int a : m_FallenTilesPositions)
		{
            m_Tiles[a]->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
            m_Tiles[a]->GetMesh()->SetVisibility(true);
		}
		
		m_FallenTilesPositions.Empty();
	}
	
	for (int i = 0; i < 70; ++i)
	{
		int id = FMath::RandRange(0, 899);

		m_Tiles[id]->GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		m_Tiles[id]->GetMesh()->SetVisibility(false);
		m_FallenTilesPositions.Add(id);
	}
}

