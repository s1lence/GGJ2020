// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameCharacter.generated.h"

UCLASS()
class AGameCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	AGameCharacter();

    void MoveForward(float Value);
    void MoveRight(float Value);

	int GetId() const { return Id; };
	void SetId(int id) { Id = id; };

protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    class UArrowComponent* m_Arrow = nullptr;

private:
	int Id = 1; // #TODO Generate ID
};

