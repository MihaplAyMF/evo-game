#pragma once

#include <memory>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "StateIdentifiers.h"
#include "ResourceIdentifiers.h"

namespace sf	
{
	class RenderWindow;
}

class StateStack;
class PlayerMove;		

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	struct Context 
	{
		Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, PlayerMove& player);
	
		sf::RenderWindow* window;
		TextureHolder*	  textures;
		FontHolder*		  fonts;
		PlayerMove*		  player;
	};

public:
				 State(StateStack& stack, Context context);
	virtual		 ~State();

	virtual bool handleEvent(const sf::Event& event) = 0;
	virtual bool update(sf::Time dt) = 0;
	virtual void draw() = 0;

protected:
	void		 requestStackPush(States stateID);
	void		 requestStackPop();
	void		 requestStateClear();

	Context		 getContext() const;

private:
	StateStack* mStack;
	Context		mContext;
};