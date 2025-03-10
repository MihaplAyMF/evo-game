#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "SettingsState.h"
#include "Settings.h"
#include "Utility.hpp"
#include "ResourceHolder.hpp"
#include "Label.h"

SettingsState::SettingsState(StateStack& stack, Context context)
	: State(stack, context)
    , mContext(context)  
    , mEvoGameSprite(context.textures->get(Textures::TitleScreen))
{
	setScale(mEvoGameSprite, sf::IntRect({0, 0}, {960, 452}));

	auto evoGameLabel = std::make_shared<GUI::Label>("", *context.fonts);
	evoGameLabel->setPosition({370, 30});
	evoGameLabel->setText("Settings");
	evoGameLabel->getText().setFillColor(sf::Color::Black);
	evoGameLabel->getText().setCharacterSize(70);

    mPlayButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	mPlayButton->setPosition({400, 150});
	mPlayButton->setText("Resolution: ");
	mPlayButton->setCallback([this] ()
	{
        
	});

	mGUIContainer.pack(evoGameLabel);
	mGUIContainer.pack(mPlayButton);

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
    else if (event.is<sf::Event::KeyPressed>())
    {
        if (event.getIf<sf::Event::KeyPressed>()->scancode == sf::Keyboard::Scan::Left)
        {
            mContext.window->close();
            mContext.window->create(sf::VideoMode({500, 500}), "SFML Window");
            mPlayButton->setText("Resolution: X, Y");
        } 
        else if (event.getIf<sf::Event::KeyPressed>()->scancode == sf::Keyboard::Scan::Right)
        {
            mPlayButton->setText("Resolution: X, Y");
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
