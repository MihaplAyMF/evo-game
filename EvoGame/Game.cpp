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


	registerStates();
	mStateStack.pushState(States::Game);
	
	/*t1.loadFromFile("Media/Textures/back.png");
	t2.loadFromFile("Media/Textures/player.png");
	t3.loadFromFile("Media/Textures/platform.png");

	t1.setSmooth(true);
	t2.setSmooth(true);
	t3.setSmooth(true);

	background.setTexture(t1);
	player.setTexture(t2);
	platform.setTexture(t3);

	background.setTextureRect(sf::IntRect(0, 0, 640, 480));

	shape.SetAsBox(30 / SCALE, 30 / SCALE);

	bdef.type = b2_dynamicBody;

	bdef.position.Set(2, 2);
	circle.m_radius = 16 / SCALE;
	pBody = World.CreateBody(&bdef);
	pBody->CreateFixture(&circle, 2);*/
	//pBody->SetUserData("player");
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


