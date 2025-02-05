#include <string>
#include <algorithm>
#include <map>

#include "PlayerMove.h"
#include "Player.h"


struct PlayerMover
{
	PlayerMover(Action type)
		: type(type)
	{ }

	void operator() (Player& player, sf::Time) const
	{	
		player.movePlayer(type);
	}

	Action type;
};

PlayerMove::PlayerMove()
{
	mKeyBinding[sf::Keyboard::W] = MoveOnLadder;
	mKeyBinding[sf::Keyboard::A] = MoveLeft;
	mKeyBinding[sf::Keyboard::D] = MoveRight;
	mKeyBinding[sf::Keyboard::F] = PressF;

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
		if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D)
			commands.push(mActionBinding[NotMove]);
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
	mActionBinding[MoveLeft].action      = derivedAction<Player>(PlayerMover(MoveLeft));
	mActionBinding[MoveRight].action     = derivedAction<Player>(PlayerMover(MoveRight));
	mActionBinding[MoveUp].action        = derivedAction<Player>(PlayerMover(MoveUp));
	mActionBinding[NotMove].action		 = derivedAction<Player>(PlayerMover(NotMove));
	mActionBinding[MoveOnLadder].action  = derivedAction<Player>(PlayerMover(MoveOnLadder));
	mActionBinding[PressF].action        = derivedAction<Player>([] (Player& player, sf::Time){player.setIsExit(true);});
}

bool PlayerMove::isRealtimeAction(Action action)
{
	switch(action)
	{
	case MoveLeft:
	case MoveRight:
	case MoveOnLadder:
	case PressF:
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
