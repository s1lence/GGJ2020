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

protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    class UArrowComponent* m_Arrow = nullptr;

};

