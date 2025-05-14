#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "SettingsState.h"
#include "Settings.h"
#include "Utility.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>

SettingsState::SettingsState(StateStack& stack, Context context)
	: State(stack, context)
    , mEvoGameSprite(context.textures->get(Textures::TitleScreen))
    , mEvoGameLabel(std::make_shared<GUI::Label>("Settings", *context.fonts))
    , mResolButton(std::make_shared<GUI::Button>(*context.fonts, *context.textures))
    , mFullscreenButton(std::make_shared<GUI::Button>(*context.fonts, *context.textures))
    , mVerticalSyncButton(std::make_shared<GUI::Button>(*context.fonts, *context.textures))
    , mShowFPSButton(std::make_shared<GUI::Button>(*context.fonts, *context.textures))
    , mLangButton(std::make_shared<GUI::Button>(*context.fonts, *context.textures))
    , mSettings(Settings::getInstance())
{

    if(mSettings.isVerSync())
        getContext().window->setVerticalSyncEnabled(true);

    bool isFullscreen = mSettings.isFullscreen();
    sf::Vector2u res = isFullscreen ?  mSettings.getMaxResolution() : mSettings.getCurrentResolution();
    setScale(mEvoGameSprite, sf::IntRect({0, 0}, {static_cast<int>(res.x), static_cast<int>(res.y)})); 
    
    mEvoGameLabel->getText().setFillColor(sf::Color::Black);

	mResolButton->setText("Resolution: " + getResolutionText(mSettings.getCurrentResolution()));	
    mResolButton->setCallback([this] () 
    { 
        if(!mSettings.isResolutionEqual())
        {
            mSettings.setCurrentResolution();
            updateWindow();
        }}
    );

    mFullscreenButton->setCallback([this] ()
	{
        mSettings.setFullscreen(!mSettings.isFullscreen());
        mSettings.setFullScreenResolution();
        updateWindow();
    });
   
    sf::RenderWindow* window = context.window;
    mVerticalSyncButton->setCallback([this, window] ()
    {
        bool newState = !mSettings.isVerSync();
        mSettings.setVerSync(newState);
        window->setVerticalSyncEnabled(newState);
        updateTextAppearance();
    });
       
    mShowFPSButton->setCallback([this]()
    {
        mSettings.setShowFPS(!mSettings.isShowFPS());
        updateTextAppearance();
    });

    mLangButton->setText("Lang: " + mSettings.getNextLang());
    mLangButton->setCallback([this]() 
    {
        mSettings.setCurrentLanguage();
    });

    updateTextAppearance();

	mGUIContainer.pack(mEvoGameLabel);
	mGUIContainer.pack(mResolButton);
    mGUIContainer.pack(mFullscreenButton);
    mGUIContainer.pack(mVerticalSyncButton);
    mGUIContainer.pack(mShowFPSButton);
    mGUIContainer.pack(mLangButton);
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
            && mResolButton->isActive() && !mSettings.isFullscreen())
        { 
            mSettings.setNextResolution(Settings::Direction::Prev);
            sf::Vector2u res = mSettings.getNextResolution();
            mResolButton->setText("Resolution: " + std::to_string(res.x) + ", " + std::to_string(res.y));
        }
        else if (event.getIf<sf::Event::KeyPressed>()->scancode == sf::Keyboard::Scan::Right
             && mResolButton->isActive() && !mSettings.isFullscreen())
        {
            mSettings.setNextResolution(Settings::Direction::Next);
            sf::Vector2u res = mSettings.getNextResolution();
            mResolButton->setText("Resolution: " + std::to_string(res.x) + ", " + std::to_string(res.y));
        }
        
        if (event.getIf<sf::Event::KeyPressed>()->scancode == sf::Keyboard::Scan::Left
            && mLangButton->isActive())
        { 
            mSettings.setNextLanguage(Settings::Direction::Prev);
            mLangButton->setText("Lang: " + mSettings.getNextLang());
        }
        else if (event.getIf<sf::Event::KeyPressed>()->scancode == sf::Keyboard::Scan::Right
             && mLangButton->isActive())
        {
            mSettings.setNextLanguage(Settings::Direction::Next);
            mLangButton->setText("Lang: " + mSettings.getNextLang());
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
    bool isFullscreen = mSettings.isFullscreen();
    sf::Vector2u res = mSettings.getCurrentResolution(); 
   
    getContext().window->close();
    if(isFullscreen)
        getContext().window->create(sf::VideoMode({res.x, res.y}), "SFML Window", sf::State::Fullscreen);
    else 
        getContext().window->create(sf::VideoMode({res.x, res.y}), "SFML Window", sf::Style::Default);
    
    res = isFullscreen ? mSettings.getMaxResolution() : mSettings.getCurrentResolution();
    setScale(mEvoGameSprite, sf::IntRect({0, 0}, {static_cast<int>(res.x), static_cast<int>(res.y)})); 
   
    if(mSettings.isVerSync())
        getContext().window->setVerticalSyncEnabled(true);
    

    updateTextAppearance();
}

void SettingsState::updateTextAppearance()
{
    bool isFullscreen = mSettings.isFullscreen();
    
    sf::Vector2u res = isFullscreen ?  mSettings.getMaxResolution() : mSettings.getCurrentResolution();

    mEvoGameLabel->getText().setCharacterSize(mSettings.getAdaptiveValue(70));
    mEvoGameLabel->setPosition({res.x / 2.f - mEvoGameLabel->getText().getGlobalBounds().size.x / 2.f, 60});

    mResolButton->getText().setCharacterSize(mSettings.getAdaptiveValue(30));
    mResolButton->setText("Resolution: " + getResolutionText(res)); 
    
    mFullscreenButton->getText().setCharacterSize(mSettings.getAdaptiveValue(30));
	mFullscreenButton->setText("Fullscreen: " + boolToString(mSettings.isFullscreen()));

    mVerticalSyncButton->getText().setCharacterSize(mSettings.getAdaptiveValue(30));
	mVerticalSyncButton->setText("Vertical sync: " + boolToString(mSettings.isVerSync()));

    mShowFPSButton->getText().setCharacterSize(mSettings.getAdaptiveValue(30));
	mShowFPSButton->setText("Show FPS: " + boolToString(mSettings.isShowFPS()));

    float resolTextWidth = mResolButton->getText().getGlobalBounds().size.x;
    float fullscreenTextWidth = mFullscreenButton->getText().getGlobalBounds().size.x;
    float maxWidth = std::max(resolTextWidth, fullscreenTextWidth);
    float centerX = res.x / 2.f - maxWidth / 2.f;

    mResolButton->setPosition({centerX, mSettings.getAdaptiveValue(200)});
    mFullscreenButton->setPosition({centerX, mSettings.getAdaptiveValue(250)});
    mVerticalSyncButton->setPosition({centerX, mSettings.getAdaptiveValue(300)});
    mShowFPSButton->setPosition({centerX, mSettings.getAdaptiveValue(350)});
    mLangButton->setPosition({centerX, mSettings.getAdaptiveValue(400)});
}

std::string SettingsState::boolToString(bool value)
{
    return value ? "Yes" : "No";
}

std::string SettingsState::getResolutionText(const sf::Vector2u& res) const
{
    return "Resolution: " + std::to_string(res.x) + ", " + std::to_string(res.y);
}
