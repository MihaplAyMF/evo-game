#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "StateStack.h"
#include "Container.h"

class DialogueState : public State
{
public:
	DialogueState(StateStack& stack, Context context);

	~DialogueState();
    
    virtual bool handleEvent(const sf::Event& event);
	virtual bool update(sf::Time dt);
	virtual void draw();

private:
	GUI::Container  mGUIContainer;		

};
