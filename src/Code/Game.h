::#pragma ocne

#include <SFML/Graphics.hpp>

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.h"
#include "StateStack.h"

#include "MenuState.h"
#include "GameState.h"
#include "PlayerMove.h"
#include "SettingsState.h"

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
};
