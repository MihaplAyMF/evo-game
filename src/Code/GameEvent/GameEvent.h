#pragma once

enum class EventType 
{
    InteractWithNPC,
    StartDialogue,
    PickupItem,
};

struct GameEvent 
{
    EventType type;
    void* payload; 
};

