#pragma once 

#include "GameEvent.h"

#include <queue>

class EventQueue {
public:
    void pushEvent(const GameEvent& event);
    bool pollEvent(GameEvent& outEvent);

private:
    std::queue<GameEvent> mEvents;
};
