#include "Game.h"

#include <filesystem>
#include <iostream>

#include "State.h"
#include "StateIdentifiers.h"
#include "SettingsState.h"
#include "Settings.h"
#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"
#include "OverState.h"

namespace fs = std::filesystem;
const sf::Time Game::timePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
    : mTextures()
    , mFonts()
    , mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
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

    mFonts.open(Fonts::Main, (path / "Media/Fonts/Sansation.ttf").string());
    mFpsLabel = std::make_shared<GUI::Label>("FPS: 0", mFonts);
    mFpsLabel->setPosition({10, 10});
    mFpsLabel->getText().setCharacterSize(20);

    mTextures.load(Textures::Tileset,     (path / "Media/Textures/nature-paltformer.png").string());
    mTextures.load(Textures::TitleScreen, (path / "Media/Textures/title-screen.png").string());

    registerStates();
	mStateStack.pushState(States::Menu);
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;

        handleInput();

        // Fixed timestep updates (може бути 0 або кілька апдейтів)
        while (timeSinceLastUpdate >= timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            update(timePerFrame); // оновлення логіки на стабільному кроці
        }

        render(); // малюємо ОСТАННІЙ відомий стан
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
	mStateStack.registerState<OverState>(States::GameOver, "Game over!");
	mStateStack.registerState<OverState>(States::GameWon, "You won!");
}
