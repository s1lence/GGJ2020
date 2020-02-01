#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GGJ2020GameInstance.generated.h"

UCLASS()
class GGJ2020_API UGGJ2020GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
    UGGJ2020GameInstance(const FObjectInitializer& ObjectInitializer);
    void Shutdown() override;
	
};
