#include "StateStack.h"

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, PlayerMove& player, NPC& npc)
	: window(&window)
	, textures(&textures)
	, fonts(&fonts)
	, player(&player)
    , interactingNPC(&npc)
{ }

State::State(StateStack& stack, Context context)
	: mStack(&stack)
	, mContext(context)
{ }

State::~State()
{ }

void State::requestStackPush(States stateID)
{
	mStack->pushState(stateID);
}

void State::requestStackPop()
{
	mStack->popState();
}

void State::requestStateClear()
{
	mStack->clearStates();
}

State::Context State::getContext() const
{
	return mContext;
}
