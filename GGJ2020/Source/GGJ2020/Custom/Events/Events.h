#pragma once
#include <functional>

enum class GameplayEventType
{
    Base,
    LeaveFromMainMenu,
};

struct EventData
{
    GameplayEventType eventType;

protected:
    EventData(const GameplayEventType& otherEventType)
        : eventType(otherEventType)
    {}
};

struct EventSubscribeData
{
    EventSubscribeData(const GameplayEventType& otherEventType, const std::function<void(const EventData&)>& otherCallback)
        : eventType(otherEventType)
        , callback(otherCallback)
    {}

    GameplayEventType eventType;
    std::function<void(const EventData&)> callback;
};

struct EventDelegateHandle
{
    EventDelegateHandle(const GameplayEventType& otherEventType, const FDelegateHandle& otherHandle)
        : eventType(otherEventType)
        , handle(otherHandle)
    {}

    GameplayEventType eventType;
    FDelegateHandle handle;
};

DECLARE_EVENT_OneParam(EventDispatcher, BaseGameEvent, const struct EventData&)
DECLARE_DERIVED_EVENT(EventDispatcher, BaseGameEvent, LeaveFromMainMenuEvent)

struct LeaveFromMainMenuEventData : public EventData
{
    using Super = EventData;

    LeaveFromMainMenuEventData()
        : Super(GameplayEventType::LeaveFromMainMenu)
    {}
};
