// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicCharacter.generated.h"

UCLASS()
class GGJ2020_API ABasicCharacter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicCharacter();

    int GetId() const { return Id; };
    void SetId(int id) { Id = id; };

    void MoveForward(float Value);
    void MoveRight(float Value);

	void Shoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnShoot();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* m_Mesh = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UBoxComponent* m_Box = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UArrowComponent* m_Arrow = nullptr;

private:
    int Id = 0; // #TODO Generate ID

};
