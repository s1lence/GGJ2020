// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ2020GameInstance.h"
#include "Custom/Events/EventDispatcher.h"


UGGJ2020GameInstance::UGGJ2020GameInstance(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    //make sure we init singletons only once
    if (!HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
    {
        EventDispatcher::GetInstance().Init();
    }
}

void UGGJ2020GameInstance::Shutdown()
{
    Super::Shutdown();

    EventDispatcher::GetInstance().Shutdown();
}


