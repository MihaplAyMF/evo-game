#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "GameState.h"
#include "Utility.hpp"
#include "ResourceHolder.hpp"
#include "Button.h"
#include "Label.h"

GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
    , mEvoGameSprite(context.textures->get(Textures::TitleScreen))
{

}

bool GameState::handleEvent(const sf::Event& event)
{
	return true;
}

bool GameState::update(sf::Time dt)
{
	return true;
}

void GameState::draw()
{
}
