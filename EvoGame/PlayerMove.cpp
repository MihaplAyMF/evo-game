#include <string>
#include <algorithm>
#include <map>

#include "PlayerMove.h"
#include "Player.h"

struct PlayerMover
{
	PlayerMover(float vx, float vy)
		: velocity(vx, vy)
	{ }

	void operator() (Player& player, sf::Time) const
	{	
		player.movePlayer(velocity);
	}

	b2Vec2 velocity;
};

PlayerMove::PlayerMove()
{
	mKeyBinding[sf::Keyboard::A] = MoveLeft;
	mKeyBinding[sf::Keyboard::D] = MoveRight;
	mKeyBinding[sf::Keyboard::W] = MoveUp;

	spacePressed = false;

	initializeAction();

	for(auto& pair : mActionBinding)
		pair.second.category = Category::Player;
}

void PlayerMove::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if(event.type == sf::Event::KeyPressed)
	{

 		if(event.key.code == sf::Keyboard::Space && !spacePressed)
		{
			commands.push(mActionBinding[MoveUp]);
			spacePressed = true;
		}
	}

	if(event.type == sf::Event::KeyReleased)
	{
		if(event.key.code == sf::Keyboard::Space)
		{
			spacePressed = false;
		}
	}
}

void PlayerMove::handleRealtimeInput(CommandQueue& commands)
{
	bool isAnyKeyPressed = false;

	for(auto pair : mKeyBinding)
	{		
		if(sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
		{
			commands.push(mActionBinding[pair.second]);
			isAnyKeyPressed = true;
		}
	}
	if(!isAnyKeyPressed)
	{
		commands.push(mActionBinding[NotMove]);
	}
}

void PlayerMove::assignKey(Action action, sf::Keyboard::Key key)
{
	for(auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if(itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}

	mKeyBinding[key] = action;
}

sf::Keyboard::Key PlayerMove::getAssigneKey(Action action) const
{
	for(auto pair : mKeyBinding)
	{
		if(pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

void PlayerMove::initializeAction()
{
	float const playerSpeed = 5.f;

	mActionBinding[MoveLeft].action      = derivedAction<Player>(PlayerMover(-playerSpeed, 0.f));
	mActionBinding[MoveRight].action     = derivedAction<Player>(PlayerMover(+playerSpeed, 0.f));
	mActionBinding[MoveUp].action        = derivedAction<Player>(PlayerMover(0.f, -playerSpeed));
	mActionBinding[NotMove].action		 = derivedAction<Player>(PlayerMover(0.f, 0.f));
}

bool PlayerMove::isRealtimeAction(Action action)
{
	switch(action)
	{
	case MoveLeft:
	case MoveRight:
		return true;
	
	default:
		return false;
	}
}

bool PlayerMove::isNotRealtimeAction(Action action)
{
	switch(action)
	{
	case MoveUp:
		return true;

	default:
		return false;
	}
}
