#pragma ocne

#include <SFML/Graphics.hpp>

#include "ResourceIdentifiers.h"
#include "PlayerMove.h"
#include "StateStack.h"
#include "Settings.h"
#include "Label.h"

class Game
{
public:
    Game();
    void run();

private:
    void handleInput();
    void update(sf::Time dt);
    void render();
    
    void registerStates();

private:
    static const sf::Time timePerFrame;

    sf::RenderWindow mWindow;
    TextureHolder    mTextures;
    FontHolder       mFonts;
	PlayerMove		 mPlayer;

    StateStack       mStateStack;

    std::shared_ptr<GUI::Label> mFpsLabel;
    Settings& mSettings;
};
