#pragma once

#include <string>
#include <vector>
#include <array>
#include <deque>
#include <map>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.h"
#include "CommandQueue.h"
#include "SpriteNode.h"
#include "Player.h"
#include "Coin.h"

class World : public sf::NonCopyable
{
public:

    explicit World(sf::RenderWindow& window, FontHolder& fonts);
    
    void update(sf::Time dt);
    void draw();

    CommandQueue& getCommandQueue(); 
    void cleanup();
    bool hasAlivePlayer();

    bool LoadFromFile(std::string filename);

private:
    void loadTextures();
    void buildScene();
    void handleCollisions();

    sf::FloatRect getViewBounds() const;
    sf::FloatRect getEvoGameBounds() const;

    enum Layer
    {
        Background,
        Air,
        LayerCount
    };

private:
    sf::RenderTarget& mTarget;
    sf::RenderTexture mSceneTexture;
    sf::View mWorldView;
    TextureHolder mTextures;
    FontHolder& mFonts;

    SceneNode mSceneGraph;
    std::array<SceneNode*, LayerCount> mSceneLayers;
    CommandQueue mCommandQueue;

    Player* mPlayer;
    std::vector<Coin*> coinBody;

    int width, height, tileWidth, tileHeight;
    int firstTileID;

};