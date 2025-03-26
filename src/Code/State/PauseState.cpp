#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <memory>

#include "PauseState.h"
#include "Utility.hpp"
#include "Button.h"
#include "Label.h"

PauseState::PauseState(StateStack& stack, Context context)
	: State(stack, context)
	, mGUIContainer()
{
	sf::Font& font = context.fonts->get(Fonts::Main);
	sf::Vector2f windowSize = context.window->getView().getSize();

    auto mPausedText = std::make_shared<GUI::Label>("Game Paused", *context.fonts);
	mPausedText->getText().setCharacterSize(70);
	centerOrigin(mPausedText->getText());
    mPausedText->setPosition({0.5f * windowSize.x, 0.4f * windowSize.y});
    mPausedText->getText().setString("Game Paused");
	
    auto returnButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	returnButton->setPosition({0.5f * windowSize.x - 100, 0.4f * windowSize.y + 75});
	returnButton->setText("Return");
	returnButton->setCallback([this] ()
	{
		requestStackPop();
	});

	auto backToMenuButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	backToMenuButton->setPosition({0.5f * windowSize.x - 100, 0.4f * windowSize.y + 125});
	backToMenuButton->setText("Back to menu");
	backToMenuButton->setCallback([this] ()
	{
		requestStateClear();
		requestStackPush(States::Menu);
	});

    mGUIContainer.pack(mPausedText);
	mGUIContainer.pack(returnButton);
	mGUIContainer.pack(backToMenuButton);
}

PauseState::~PauseState()
{
}

bool PauseState::handleEvent(const sf::Event & event)
{
	mGUIContainer.handleEvent(event);
	return false;
}

bool PauseState::update(sf::Time dt)
{
	return false;
}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mGUIContainer);
}
