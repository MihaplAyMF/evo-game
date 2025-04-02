#pragma once

#include <string>
#include <array>
#include <map>

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "ResourceIdentifiers.h"
#include "CommandQueue.h"
#include "Player.h"
#include "Label.h"
   
#include "MapLoader.h"

class World 
{
public:

    explicit World(sf::RenderWindow& window, TextureHolder& texture, FontHolder& fonts);
    
    World(const World&) = delete;
    World& operator=(const World&) = delete;

    void update(sf::Time dt);
    void draw();

    CommandQueue& getCommandQueue(); 
    void clean();
    bool hasAlivePlayer();

private:
    void buildScene();
    void handleCollisions();
    void updateCamera();

    bool loadTexture(std::string filename);
    bool loadFromFile(std::string filename);

    void createHUD();
    void drawHUD();
    void playerUpdate();

    void cleanup();
    void saveFirstGameState();
    void saveGameState();
    void loadGameState();
    void switchMap(const std::string& filename);
    void changeMapPlayerOutsideView();

    sf::FloatRect getViewBounds() const;
    sf::FloatRect getEvoGameBounds() const;

private:
    sf::RenderTarget& mTarget;
    sf::RenderTexture mSceneTexture;
    sf::View mWorldView, mHUDView;
    TextureHolder& mTextures;
    FontHolder& mFonts;
    std::string mCurrentMap;

    SceneNode mSceneGraph;
    std::array<SceneNode*, LayerCount> mSceneLayers;
    CommandQueue mCommandQueue;
    
    b2World& mWorld;
    float mBoxScale;
    float mGameScale;

    MapLoader mMapLoader;

    Player* mPlayer;
    sf::Vector2f mGlobalPos;
    sf::Vector2f mPlayerPos;
    sf::Vector2f mStartPos;

    sf::Sprite mHeartSprite;
    sf::Sprite mCoinSprite;
    GUI::Label mCoinLabel;
    int mCoinCollected;
    std::map<std::string, std::set<int>> mCoinIDCollected;

};
