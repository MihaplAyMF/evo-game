#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "SettingsState.h"
#include "Utility.hpp"
#include "ResourceHolder.hpp"
#include "Button.h"
#include "Label.h"

SettingsState::SettingsState(StateStack& stack, Context context)
	: State(stack, context)
    , mEvoGameSprite(context.textures->get(Textures::TitleScreen))
{
	setScale(mEvoGameSprite, sf::IntRect({0, 0}, {960, 452}));

	auto evoGameLabel = std::make_shared<GUI::Label>("", *context.fonts);
	evoGameLabel->setPosition({370, 30});
	evoGameLabel->setText("Settings");
	evoGameLabel->getText().setFillColor(sf::Color::Black);
	evoGameLabel->getText().setCharacterSize(70);

	auto playButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	playButton->setPosition({400, 150});
	playButton->setText("test");
	playButton->setCallback([this] ()
	{
	});

	mGUIContainer.pack(evoGameLabel);
	mGUIContainer.pack(playButton);

}

bool SettingsState::handleEvent(const sf::Event& event)
{
    if (event.is<sf::Event::KeyReleased>())
    {
        if (event.getIf<sf::Event::KeyReleased>()->scancode == sf::Keyboard::Scan::Escape)
        {
            requestStackPop();
        }
    }

    mGUIContainer.handleEvent(event);
	return true;
}

bool SettingsState::update(sf::Time dt)
{
	mGUIContainer.update(dt);
	return true;
}

void SettingsState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(mEvoGameSprite);
	window.draw(mGUIContainer);
}
