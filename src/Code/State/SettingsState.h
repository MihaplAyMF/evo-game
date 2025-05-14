#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

#include "Settings.h"
#include "StateStack.h"
#include "Container.h"
#include "Button.h"
#include "Label.h"

class SettingsState : public State
{
public:
	SettingsState(StateStack& stack, Context context);

	virtual bool handleEvent(const sf::Event& event);
	virtual bool update(sf::Time dt);
	virtual void draw();

    void updateWindow();
    void updateTextAppearance();

private:
    std::string boolToString(bool value);
    std::string getResolutionText(const sf::Vector2u& res) const;

    sf::Sprite			          mEvoGameSprite;
    std::shared_ptr<GUI::Button>  mResolButton;
    std::shared_ptr<GUI::Button>  mFullscreenButton;
    std::shared_ptr<GUI::Button>  mVerticalSyncButton;
    std::shared_ptr<GUI::Button>  mShowFPSButton;
    std::shared_ptr<GUI::Button>  mLangButton;

    std::shared_ptr<GUI::Label>   mEvoGameLabel;
	GUI::Container		          mGUIContainer;

    Settings& mSettings;
};
