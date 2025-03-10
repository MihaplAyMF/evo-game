#pragma once

#include <vector>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "StateStack.h"
#include "Container.h"
#include "Button.h"

class SettingsState : public State
{
public:
	SettingsState(StateStack& stack, Context context);

	virtual bool handleEvent(const sf::Event& event);
	virtual bool update(sf::Time dt);
	virtual void draw();

private:
	sf::Sprite			          mEvoGameSprite;
    std::shared_ptr<GUI::Button>  mPlayButton;
	GUI::Container		          mGUIContainer;
    Context                       mContext;
};
