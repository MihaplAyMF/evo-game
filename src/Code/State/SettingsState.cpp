#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "SettingsState.h"
#include "Settings.h"
#include "Utility.hpp"
#include "ResourceHolder.hpp"

SettingsState::SettingsState(StateStack& stack, Context context)
	: State(stack, context)
    , mEvoGameSprite(context.textures->get(Textures::TitleScreen))
    , mEvoGameLabel(std::make_shared<GUI::Label>("Settings", *context.fonts))
    , mResolButton(std::make_shared<GUI::Button>(*context.fonts, *context.textures))
    , mFullscreenButton(std::make_shared<GUI::Button>(*context.fonts, *context.textures))
{
    sf::Vector2u res = Settings::getInstance().getResolution();
    setScale(mEvoGameSprite, sf::IntRect({0, 0}, {static_cast<int>(res.x), static_cast<int>(res.y)})); 

	mEvoGameLabel->getText().setFillColor(sf::Color::Black);
     
    res = Settings::getInstance().getCurrentResolution();
	mResolButton->setText("Resolution: " + std::to_string(res.x) + ", " + std::to_string(res.y));	
    mResolButton->setCallback([this] ()
	{ 
        if(!Settings::getInstance().isResolutionEqual())
        {
            Settings::getInstance().setResolution();
            updateWindow();
        }
    });

    mFullscreenButton->setCallback([this] ()
	{
        Settings::getInstance().setFullscreen(!Settings::getInstance().isFullscreen());
        updateWindow();
    });

    updateTextAppearance();

	mGUIContainer.pack(mEvoGameLabel);
	mGUIContainer.pack(mResolButton);
    mGUIContainer.pack(mFullscreenButton);
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
        if (event.getIf<sf::Event::KeyPressed>()->scancode == sf::Keyboard::Scan::Left
            && mResolButton->isActive())
        { 
            Settings::getInstance().setNextResolution(Settings::Direction::Prev);
            sf::Vector2u res = Settings::getInstance().getNextResolution();
            mResolButton->setText("Resolution: " + std::to_string(res.x) + ", " + std::to_string(res.y));
        }
        else if (event.getIf<sf::Event::KeyPressed>()->scancode == sf::Keyboard::Scan::Right
            && mResolButton->isActive())
        {
            Settings::getInstance().setNextResolution(Settings::Direction::Next);
            sf::Vector2u res = Settings::getInstance().getNextResolution();
            mResolButton->setText("Resolution: " + std::to_string(res.x) + ", " + std::to_string(res.y));
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

void SettingsState::updateWindow()
{
    sf::Vector2u res = Settings::getInstance().getResolution();
    bool isFullscreen = Settings::getInstance().isFullscreen();
    
    getContext().window->close();
    if(isFullscreen)
        getContext().window->create(sf::VideoMode({res.x, res.y}), "SFML Window", sf::State::Fullscreen);
    else 
        getContext().window->create(sf::VideoMode({res.x, res.y}), "SFML Window", sf::Style::Default);

    setScale(mEvoGameSprite, sf::IntRect({0, 0}, {static_cast<int>(res.x), static_cast<int>(res.y)})); 
    updateTextAppearance();
}

void SettingsState::updateTextAppearance()
{
    sf::Vector2u res = Settings::getInstance().getResolution();

    mEvoGameLabel->getText().setCharacterSize(Settings::getInstance().getAdaptiveValue(70));
    mEvoGameLabel->setPosition({res.x / 2.f - mEvoGameLabel->getText().getGlobalBounds().size.x / 2.f, 60});

    mResolButton->getText().setCharacterSize(Settings::getInstance().getAdaptiveValue(30));
    mResolButton->setText(mResolButton->getText().getString()); 
    
    mFullscreenButton->getText().setCharacterSize(Settings::getInstance().getAdaptiveValue(30));
	mFullscreenButton->setText("Fullscreen: " + std::to_string(Settings::getInstance().isFullscreen()));

    float resolTextWidth = mResolButton->getText().getGlobalBounds().size.x;
    float fullscreenTextWidth = mFullscreenButton->getText().getGlobalBounds().size.x;
    float maxWidth = std::max(resolTextWidth, fullscreenTextWidth);
    float centerX = res.x / 2.f - maxWidth / 2.f;

    mResolButton->setPosition({centerX, Settings::getInstance().getAdaptiveValue(200)});
    mFullscreenButton->setPosition({centerX, Settings::getInstance().getAdaptiveValue(250)});
}

