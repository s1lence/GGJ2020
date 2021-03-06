// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class GGJ2020_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable)
	void SetId(int id) { m_Id = id; }
	int GetId() { return m_Id; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UStaticMeshComponent* GetMesh() { return m_Mesh; }

private:
	UPROPERTY()
	class UStaticMeshComponent* m_Mesh = nullptr;

	int m_Id = 0;
};
