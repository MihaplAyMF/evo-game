
#include "EventQueue.h"

void EventQueue::pushEvent(const GameEvent& event)
{
    mEvents.push(event); 
}

bool EventQueue::pollEvent(GameEvent& outEvent)
{
    if (mEvents.empty())
        return false;

    outEvent = mEvents.front(); 
    mEvents.pop();              
    return true;
}
