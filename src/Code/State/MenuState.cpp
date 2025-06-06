#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "MenuState.h"
#include "Settings.h"
#include "Utility.hpp"
#include "Button.h"
#include "Label.h"

MenuState::MenuState(StateStack& stack, Context context)
	: State(stack, context)
    , mEvoGameSprite(context.textures->get(Textures::TitleScreen))
{
    Settings& set = Settings::getInstance();
    bool isFullscreen = set.isFullscreen();
    
    sf::Vector2u res = isFullscreen ?  set.getMaxResolution() : set.getCurrentResolution();

	setScale(mEvoGameSprite, sf::IntRect({0, 0}, {static_cast<int>(res.x), static_cast<int>(res.y)})); 

	auto evoGameLabel = std::make_shared<GUI::Label>("", *context.fonts);
	evoGameLabel->setText("EvoGame");
    evoGameLabel->getText().setCharacterSize(Settings::getInstance().getAdaptiveValue(70));
    evoGameLabel->setPosition({res.x / 2.f - evoGameLabel->getText().getGlobalBounds().size.x / 2.5f, 30});
	evoGameLabel->getText().setFillColor(sf::Color::Black);

    auto playButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	playButton->setText(_("Play"));
    playButton->getText().setCharacterSize(Settings::getInstance().getAdaptiveValue(30));

	auto settingsButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	settingsButton->setText(_("Settings"));
    settingsButton->getText().setCharacterSize(Settings::getInstance().getAdaptiveValue(30));
	
    auto quitButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    quitButton->setText(_("Quit"));
    quitButton->getText().setCharacterSize(Settings::getInstance().getAdaptiveValue(30));

    int spriteSize = 16 * 4;
    
    float maxWidth = std::max({
        playButton->getText().getGlobalBounds().size.x + spriteSize,
        settingsButton->getText().getGlobalBounds().size.x + spriteSize,
        quitButton->getText().getGlobalBounds().size.x + spriteSize
    });
        
    float startX = res.x / 2.f - maxWidth / 2.f;

    playButton->setPosition({startX, Settings::getInstance().getAdaptiveValue(175)});
	playButton->setCallback([this] ()
	{
		requestStackPop();
		requestStackPush(States::Game);
	});

	settingsButton->setPosition({startX, Settings::getInstance().getAdaptiveValue(250)});
	settingsButton->setCallback([this] ()
	{
        requestStackPop();
		requestStackPush(States::Settings);
	});

	quitButton->setPosition({startX, Settings::getInstance().getAdaptiveValue(325)});
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
