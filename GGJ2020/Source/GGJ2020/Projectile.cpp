// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Sphere"));
	if (MeshAsset.Succeeded())
	{
		MeshBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileBody"));
		MeshBody->SetStaticMesh(MeshAsset.Object);

		RootComponent = MeshBody;
	}
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::AddForce(FVector const &force)
{
	MeshBody->AddForce(force, NAME_None, true);
}

