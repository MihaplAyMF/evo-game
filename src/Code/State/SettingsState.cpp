#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "SettingsState.h"
#include "Settings.h"
#include "Utility.hpp"
#include "ResourceHolder.hpp"

SettingsState::SettingsState(StateStack& stack, Context context)
	: State(stack, context)
    , mEvoGameSprite(context.textures->get(Textures::TitleScreen))
    , mEvoGameLabel(std::make_shared<GUI::Label>("", *context.fonts))
    , mPlayButton(std::make_shared<GUI::Button>(*context.fonts, *context.textures))
{
    sf::Vector2u res = Settings::getInstance().getResolution();
    setScale(mEvoGameSprite, sf::IntRect({0, 0}, {static_cast<int>(res.x), static_cast<int>(res.y)})); 

    mEvoGameLabel->setText("Settings");
	mEvoGameLabel->getText().setFillColor(sf::Color::Black);
	mEvoGameLabel->getText().setCharacterSize(Settings::getInstance().getAdaptiveValue(70));
    mEvoGameLabel->setPosition({res.x / 2.f - mEvoGameLabel->getText().getGlobalBounds().size.x / 2.f, 60});

	mPlayButton->setText("Resolution: " + std::to_string(res.x) + ", " + std::to_string(res.y));	
    mPlayButton->setPosition({res.x / 2.f - mPlayButton->getText().getGlobalBounds().size.x / 2.f, Settings::getInstance().getAdaptiveValue(200)});
    mPlayButton->setCallback([this, mContext = context] ()
	{
        Settings::getInstance().setResolution();
        sf::Vector2u res = Settings::getInstance().getResolution();
        
        setScale(mEvoGameSprite, sf::IntRect({0, 0}, {static_cast<int>(res.x), static_cast<int>(res.y)})); 

        mEvoGameLabel->getText().setCharacterSize(Settings::getInstance().getAdaptiveValue(70));
        mEvoGameLabel->setPosition({res.x / 2.f - mEvoGameLabel->getText().getGlobalBounds().size.x / 2.f, 60});

        mPlayButton->setPosition({res.x / 2.f - mPlayButton->getText().getGlobalBounds().size.x / 2.f, Settings::getInstance().getAdaptiveValue(200)});
        
        mContext.window->close();
        mContext.window->create(sf::VideoMode({res.x, res.y}), "SFML Window");
	});

	mGUIContainer.pack(mEvoGameLabel);
	mGUIContainer.pack(mPlayButton);
}

bool SettingsState::handleEvent(const sf::Event& event)
{
    if (event.is<sf::Event::KeyReleased>())
    {
        if (event.getIf<sf::Event::KeyReleased>()->scancode == sf::Keyboard::Scan::Escape)
        {
            requestStackPop();
            requestStackPush(States::Menu);
        }
    }
    else if (event.is<sf::Event::KeyPressed>())
    {
        if (event.getIf<sf::Event::KeyPressed>()->scancode == sf::Keyboard::Scan::Left)
        { 
            Settings::getInstance().setNextResolution(Settings::Direction::Prev);
            sf::Vector2u res = Settings::getInstance().getNextResolution();
            mPlayButton->setText("Resolution: " + std::to_string(res.x) + ", " + std::to_string(res.y));
        }
        else if (event.getIf<sf::Event::KeyPressed>()->scancode == sf::Keyboard::Scan::Right)
        {
            Settings::getInstance().setNextResolution(Settings::Direction::Next);
            sf::Vector2u res = Settings::getInstance().getNextResolution();
            mPlayButton->setText("Resolution: " + std::to_string(res.x) + ", " + std::to_string(res.y));
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
