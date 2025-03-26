#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "OverState.h"
#include "Utility.hpp"
#include "Player.h"
#include "ResourceHolder.hpp"

OverState::OverState(StateStack& stack, Context context, const std::string& text)
	: State(stack, context)
    , mGameOverText(std::make_shared<GUI::Label>(text, *context.fonts))
	, mElapsedTime(sf::Time::Zero)
{
	sf::Font& font = context.fonts->get(Fonts::Main);
	sf::Vector2f windowSize(context.window->getSize());

	mGameOverText->getText().setCharacterSize(70);
	centerOrigin(mGameOverText->getText());
	mGameOverText->setPosition({0.5f * windowSize.x, 0.4f * windowSize.y});
    
    mGUIContainer.pack(mGameOverText);
}

bool OverState::handleEvent(const sf::Event& event)
{
	return false;
}

bool OverState::update(sf::Time dt)
{
	mElapsedTime += dt;
	if(mElapsedTime > sf::seconds(3))
	{
		requestStateClear();
		requestStackPush(States::Menu);
	}
	return false;
}

void OverState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mGUIContainer);
}
