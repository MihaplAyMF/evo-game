#pragma once

#include <map>

#include <SFML/Window/Event.hpp>

#include "CommandQueue.h"
#include "DataTables.h"

class PlayerMove
{
public:

	enum MoveDirection
	{
		None = 0,
		Up = 1,
		Down = 2,
		Left = 4,
		Right = 8
	};

	PlayerMove();

	void			  handleEvent(const sf::Event& event, CommandQueue& commands);
	void			  handleRealtimeInput(CommandQueue& commands);

	void			  assignKey(Action action, sf::Keyboard::Scan scan);
	sf::Keyboard::Scan getAssigneKey(Action action) const;

private:
	void			  initializeAction();
	static bool		  isRealtimeAction(Action action);
	static bool		  isNotRealtimeAction(Action action);

	std::map<sf::Keyboard::Scan, Action> mKeyBinding;
	std::map<Action, Command>			mActionBinding;
	MoveDirection						mDirect;
	bool								spacePressed;

};
