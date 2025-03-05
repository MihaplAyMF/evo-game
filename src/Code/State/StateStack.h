#pragma once

#include <vector>
#include <map>
#include <functional>
#include <utility>

#include <SFML/Window/Event.hpp>

#include "StateIdentifiers.h"
#include "State.h"

namespace sg
{
    class Event;
    class RenderWindow;
}

class StateStack
{
public:
    enum Action
    {
        Push,
        Pop,
        Clear,
    };

public:
	explicit StateStack(State::Context context);

	template<typename T>
	void registerState(States stateID);

	void update(sf::Time dt);
	void draw();
	void handleEvent(const sf::Event& event);

	void pushState(States stateID);
	void popState();
	void clearStates();

	bool isEmpty() const;

private:
	State::Ptr createState(States stateID);
	void applyPendingChanges();

	struct PendingChange
	{
		explicit PendingChange(Action action, States stateID = States::None);

		Action action;
		States stateID;
	};

	std::vector<State::Ptr> mStack;
	std::vector<PendingChange> mPendingList;
	State::Context mContext;
	std::map<States, std::function<State::Ptr()>> mFactories;
};

template<typename T>
void StateStack::registerState(States stateID)
{
	mFactories[stateID] = [this]()
	{
		return State::Ptr(new T(*this, mContext));
	};
}
