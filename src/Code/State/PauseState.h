#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "StateStack.h"
#include "Container.h"

class PauseState : public State
{
public:
	PauseState(StateStack& stack, Context context);

	~PauseState();
	
    virtual bool handleEvent(const sf::Event& event);
	virtual bool update(sf::Time dt);
	virtual void draw();

private:
	GUI::Container  mGUIContainer;		

};
