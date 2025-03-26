#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.h"
#include "Container.h"
#include "Label.h"

class OverState : public State
{
public:
	OverState(StateStack& stack, Context context, const std::string& text);

	virtual bool handleEvent(const sf::Event& event);
	virtual bool update(sf::Time dt);
	virtual void draw();

private:
    std::shared_ptr<GUI::Label>   mGameOverText; 
	GUI::Container		          mGUIContainer;
	
    sf::Time                      mElapsedTime;
};

