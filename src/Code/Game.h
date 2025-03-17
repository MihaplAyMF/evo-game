#pragma ocne

#include <SFML/Graphics.hpp>

#include "ResourceHolder.hpp" // IWYU pragma: keep 
#include "ResourceIdentifiers.h"
#include "PlayerMove.h"
#include "StateStack.h"

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
