// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectToRepair.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Custom/Events/EventDispatcher.h"
#include "Projectile.h"


// Sets default values
AObjectToRepair::AObjectToRepair()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectMesh"));
	RootComponent = ObjectMesh;
	ConstructorHelpers::FObjectFinder<UStaticMesh> ObjectMeshAsset(TEXT("/Engine/BasicShapes/Cube"));
	if (ObjectMeshAsset.Object)
	{
		ObjectMesh->SetStaticMesh(ObjectMeshAsset.Object);
	}

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->AttachTo(RootComponent);

	BoxComponent->SetBoxExtent(FVector(55.0f, 55.0f, 55.0f));

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AObjectToRepair::BeginOverlap);
}

// Called when the game starts or when spawned
void AObjectToRepair::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObjectToRepair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObjectToRepair::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (AProjectile* projectile = Cast<AProjectile>(OtherActor))
	{
		projectile->Destroy();
		return;
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Began overlap!"));
	UE_LOG(LogTemp, Warning, TEXT("Began overlap!"));

	if (AGameCharacter* player = Cast<AGameCharacter>(OtherActor))
	{
		SendRepairEvent(player->GetId(), player->TakeDetailsFromPlayersToObject()); // #TODO Pass player->TakeDetailsFromPlayersToObject as second parameter
	}
}

void AObjectToRepair::SendRepairEvent(int playerIndex, int amountOfItemsBringed)
{
	if (BaseGameEvent* repairEvent = EventDispatcher::GetInstance().GetEvent(GameplayEventType::PlayerRepairedObject))
	{
		repairEvent->Broadcast(PlayerRepairedObjectEventData(playerIndex, amountOfItemsBringed));
	}
}

//void AObjectToRepair::SendRepairEvent_Implementation()
//{
//
//}