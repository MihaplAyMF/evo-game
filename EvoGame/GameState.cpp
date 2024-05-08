#include "GameState.h"

GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
	, mWorld(*context.window, *context.fonts)
	, mPlayer(*context.player)
{
}

bool GameState::handleEvent(const sf::Event& event)
{
	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleEvent(event, commands);

	if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		requestStackPop();
		requestStackPush(States::Menu);
	}

	return true;
}

bool GameState::update(sf::Time dt)
{
	mWorld.update(dt);

	//if(!mWorld.hasAliveEagle())
	//{
	//	requestStackPush(States::GameOver);
	//}
	//else if(!mWorld.hasAlivePlayer())
	//{
	//	requestStackPush(States::GameOver);
	//}

	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleRealtimeInput(commands);

	return true;
}

void GameState::draw()
{
	mWorld.draw();
}