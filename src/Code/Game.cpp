#include "Game.h"

#include <filesystem>

#include "DialogueState.h"
#include "State.h"
#include "StateIdentifiers.h"
#include "SettingsState.h"
#include "Settings.h"
#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"
#include "DialogueState.h"
#include "OverState.h"

namespace fs = std::filesystem;
const sf::Time Game::timePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
    : mTextures()
    , mFonts()
    , mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer, mEvent))
    , mFpsLabel()
    , mSettings(Settings::getInstance())
{
    sf::ContextSettings settings;
  
    sf::Vector2u res = mSettings.getCurrentResolution();

    if(mSettings.isFullscreen())
        mWindow.create(sf::VideoMode({res.x, res.y}), "SFML Window", sf::State::Fullscreen);
    else 
        mWindow.create(sf::VideoMode({res.x, res.y}), "SFML Window", sf::Style::Default);
    
    if(mSettings.isVerSync())
        mWindow.setVerticalSyncEnabled(true);
    
    fs::path path = fs::current_path();

    mFonts.open(Fonts::Main, (path / "Media/Fonts/Roboto-VariableFont_wdth,wght.ttf").string());
    mFpsLabel = std::make_shared<GUI::Label>("FPS: ", mFonts);
    mFpsLabel->getText().setCharacterSize(20);
    mFpsLabel->setPosition({40, 20});
    mFpsLabel->setText("FPS: ");


    mTextures.load(Textures::Tileset,     (path / "Media/Textures/nature-paltformer.png").string());
    mTextures.load(Textures::TitleScreen, (path / "Media/Textures/title-screen.png").string());

    registerStates();
	mStateStack.pushState(States::Menu);
}

void Game::run()
{
    const sf::Time timePerFrame = sf::seconds(1.f / 60.f);
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    sf::Clock fpsClock;
    int frameCount = 0;

    while (mWindow.isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        frameCount++;

        handleInput();

        while (timeSinceLastUpdate >= timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            update(timePerFrame);
        }

        if (fpsClock.getElapsedTime() >= sf::seconds(1.f))
        {
            mFpsLabel->setText("FPS: " + std::to_string(frameCount));
            frameCount = 0;
            fpsClock.restart();
        }

        render();
    }
}

void Game::handleInput()
{
	while(const std::optional event = mWindow.pollEvent())
	{
        mStateStack.handleEvent(*event);
        if (event->is<sf::Event::Closed>() || mStateStack.isEmpty())
        {
            mWindow.close();
        }
    }
}

void Game::update(sf::Time dt)
{
    mStateStack.update(dt);
}

void Game::render()
{
    mWindow.clear(sf::Color::Black);
    mStateStack.draw();

    if(mSettings.isShowFPS())
        mWindow.draw(*mFpsLabel);
    
    mWindow.display();
}

void Game::registerStates()
{
    mStateStack.registerState<MenuState>(States::Menu);
    mStateStack.registerState<GameState>(States::Game);
    mStateStack.registerState<SettingsState>(States::Settings);
    mStateStack.registerState<PauseState>(States::Pause);
    mStateStack.registerState<DialogueState>(States::Dialogue);
	mStateStack.registerState<OverState>(States::GameOver, "Game over!");
	mStateStack.registerState<OverState>(States::GameWon, "You won!");
}
