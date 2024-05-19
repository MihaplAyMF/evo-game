#include "Game.h"

#include "State.h"
#include "StateIdentifiers.h"

#include "GameState.h"
#include "MenuState.h"

const sf::Time Game::timePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
	: mWindow(sf::VideoMode(960, 452), "EvoGame", sf::Style::Close)
	, mTextures()
	, mFonts()
	, mPlayer()
	, mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
{
	mFonts.load(Fonts::Main, "Media/Fonts/Sansation.ttf");

	mTextures.load(Textures::Tileset,     "Media/Textures/nature-paltformer.png");
	mTextures.load(Textures::TitleScreen, "Media/Textures/title-screen.png");
	//mTextures.load(Textures::Buttons,   "Media/Textures/buttons.png");

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

			if(mStateStack.isEmpty())
				mWindow.close();
		}
		render();
	}
}

void Game::handleInput()
{
	sf::Event event;
	while(mWindow.pollEvent(event))
	{
		mStateStack.handleEvent(event);

		if(event.type == sf::Event::Closed)
			mWindow.close();
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
}


