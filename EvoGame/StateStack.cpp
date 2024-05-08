#include "StateStack.h"

#include <cassert>

StateStack::StateStack(State::Context context)
    : mStack()
    , mPendingList()
    , mContext(context)
    , mFactories()
{ }

bool StateStack::isEmpty() const
{
    return mStack.empty();
}

State::Ptr StateStack::createState(States stateID)
{
    auto found = mFactories.find(stateID);
    assert(found != mFactories.end());

    return found->second();
}

void StateStack::applyPendingChanges()
{
    for(PendingChange change : mPendingList)
    {
         switch(change.action)
        {
        case Push:
            mStack.push_back(createState(change.stateID));
            break;
        case Pop:
            mStack.pop_back();
            break;
        case Clear:
            mStack.clear();
            break;
        }
    }
    mPendingList.clear();
}

void StateStack::update(sf::Time dt)
{
    for(auto itr = mStack.rbegin(); itr != mStack.rend(); itr++)
    {
        if(!(*itr)->update(dt))
            break;
    }

    applyPendingChanges();
}

void StateStack::draw()
{
    for(State::Ptr& state : mStack)
    {
        state->draw();
    }
}

void StateStack::handleEvent(const sf::Event& event)
{
    for(auto itr = mStack.rbegin(); itr != mStack.rend(); itr++)
    {
        if(!(*itr)->handleEvent(event))
            return;
    }

    applyPendingChanges();
}

void StateStack::pushState(States stateID)
{
    mPendingList.push_back(PendingChange(Push, stateID));
}

void StateStack::popState()
{
    mPendingList.push_back(PendingChange(Pop));
}

void StateStack::clearStates()
{
    mPendingList.push_back(PendingChange(Clear));
}

StateStack::PendingChange::PendingChange(Action action, States stateID)
    : action(action)
    , stateID(stateID)
{ }
