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

namespace fs = std::filesystem;
const sf::Time Game::timePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
    : mTextures()
    , mFonts()
    , mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
{
    sf::ContextSettings settings;
 std::cout << "OpenGL Context Version: " << settings.majorVersion << "." << settings.minorVersion << std::endl;
   
    sf::Vector2u res = Settings::getInstance().getCurrentResolution();

    if(Settings::getInstance().isFullscreen())
        mWindow.create(sf::VideoMode({res.x, res.y}), "SFML Window", sf::State::Fullscreen);
    else 
        mWindow.create(sf::VideoMode({res.x, res.y}), "SFML Window", sf::Style::Default);

    fs::path path = fs::current_path();

    mFonts.open(Fonts::Main, (path / "Media/Fonts/Sansation.ttf").string());

    mTextures.load(Textures::Tileset,     (path / "Media/Textures/nature-paltformer.png").string());
    mTextures.load(Textures::TitleScreen, (path / "Media/Textures/title-screen.png").string());

    registerStates();
	mStateStack.pushState(States::Menu);
}

void Game::run()
{ 
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    
    while(mWindow.isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        while(timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;

            handleInput();
            update(timePerFrame);

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
    mWindow.display();
}

void Game::registerStates()
{
    mStateStack.registerState<MenuState>(States::Menu);
    mStateStack.registerState<GameState>(States::Game);
    mStateStack.registerState<SettingsState>(States::Settings);
    mStateStack.registerState<PauseState>(States::Pause);
}
