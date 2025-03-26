#include "GameState.h"

GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
	, mWorld(*context.window, *context.textures, *context.fonts)
	, mPlayer(*context.player)
{
}

bool GameState::handleEvent(const sf::Event& event)
{
	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleEvent(event, commands);

    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
	    {
		    requestStackPush(States::Pause);
            //mWorld.clean();
        }
	}

	return true;
}

GameState::~GameState()
{
    mWorld.clean();    
}

bool GameState::update(sf::Time dt)
{
	mWorld.update(dt);

	//if(!mWorld.hasAliveEagle())
	//{
	//	requestStackPush(States::GameOver);
	//}
	//else 
	if(!mWorld.hasAlivePlayer())
	{
		mWorld.clean();
		requestStackPop();
		requestStackPush(States::Menu);
	}

	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleRealtimeInput(commands);

	return true;
}

void GameState::draw()
{
	mWorld.draw();
}
