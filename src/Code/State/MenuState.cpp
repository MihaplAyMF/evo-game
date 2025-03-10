#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "MenuState.h"
#include "Settings.h"
#include "Utility.hpp"
#include "ResourceHolder.hpp"
#include "Button.h"
#include "Label.h"

const int mapWidth = Settings::getInstance().getWidth();
const int mapHeight = Settings::getInstance().getHeight();

MenuState::MenuState(StateStack& stack, Context context)
	: State(stack, context)
    , mEvoGameSprite(context.textures->get(Textures::TitleScreen))
{
	setScale(mEvoGameSprite, sf::IntRect({0, 0}, {mapWidth, mapHeight}));

	auto evoGameLabel = std::make_shared<GUI::Label>("", *context.fonts);
	evoGameLabel->setPosition({370, 30});
	evoGameLabel->setText("MyGame");
	evoGameLabel->getText().setFillColor(sf::Color::Black);
	evoGameLabel->getText().setCharacterSize(70);

	auto playButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	playButton->setPosition({400, 150});
	playButton->setText("Play");
	playButton->setCallback([this] ()
	{
		requestStackPop();
		requestStackPush(States::Game);
	});

	auto settingsButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	settingsButton->setPosition({400, 200});
	settingsButton->setText("Settings");
	settingsButton->setCallback([this] ()
	{
		requestStackPush(States::Settings);
	});

	auto quitButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	quitButton->setPosition({400, 250});
	quitButton->setText("Quit");
	quitButton->setCallback([this] ()
	{
		requestStackPop();
	});

	mGUIContainer.pack(evoGameLabel);
	mGUIContainer.pack(playButton);
	mGUIContainer.pack(settingsButton);
	mGUIContainer.pack(quitButton);

}

bool MenuState::handleEvent(const sf::Event& event)
{ 
    if (const auto* keyEvent = event.getIf<sf::Event::KeyPressed>())
    {
        if (keyEvent->scancode == sf::Keyboard::Scan::Escape)
        {
		    requestStackPop();
        }
    }
	mGUIContainer.handleEvent(event);
	return true;
}

bool MenuState::update(sf::Time dt)
{
	mGUIContainer.update(dt);
	return true;
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(mEvoGameSprite);
	window.draw(mGUIContainer);
}
