#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "MenuState.h"
#include "Utility.hpp"
#include "ResourceHolder.hpp"
#include "Button.h"

MenuState::MenuState(StateStack& stack, Context context)
	: State(stack, context)
{
	sf::Texture& texture = context.textures->get(Textures::TitleScreen);
	mEvoGameSprite.setTexture(texture);
	//setScale(mEvoGameSprite, sf::IntRect(0, 0, 700, 250));
	/*mEvoGameSprite.setPosition(100, 50);

	auto onePlayButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	onePlayButton->setPosition(300, 400);
	onePlayButton->setText("1 PLAYER");
	onePlayButton->setCallback([this] ()
	{
		requestStackPop();
		requestStackPush(States::Game);
	});

	auto twoPlayButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	twoPlayButton->setPosition(300, 500);
	twoPlayButton->setText("2 PLAYER");
	twoPlayButton->setCallback([this] ()
	{

	});

	auto quitButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	quitButton->setPosition(300, 600);
	quitButton->setText("QUIT");
	quitButton->setCallback([this] ()
	{
		requestStackPop();
	});

	mGUIContainer.pack(onePlayButton);
	mGUIContainer.pack(twoPlayButton);
	mGUIContainer.pack(quitButton);*/
}

bool MenuState::handleEvent(const sf::Event& event)
{
	//mGUIContainer.handleEvent(event);
	return true;
}

bool MenuState::update(sf::Time dt)
{
	//mGUIContainer.update(dt);
	return true;
}

void MenuState::draw()
{
	//sf::RenderWindow& window = *getContext().window;

	//window.setView(window.getDefaultView());

	//window.draw(mBattleCitySprite);
	//window.draw(mGUIContainer);
}
