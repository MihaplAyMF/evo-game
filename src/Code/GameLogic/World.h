#pragma once

#include <SFML/System/Vector2.hpp>
#include <string>
#include <array>

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "ResourceIdentifiers.h"
#include "CommandQueue.h"
#include "MapManager.h"
#include "EventQueue.h"
#include "Player.h"
#include "Label.h"

class World 
{
public:

    explicit World(sf::RenderWindow& window, TextureHolder& texture, FontHolder& fonts, EventQueue& event);
    
    World(const World&) = delete;
    World& operator=(const World&) = delete;

    void update(sf::Time dt);
    void draw();

    CommandQueue& getCommandQueue(); 
    void clean();
    bool hasAlivePlayer();
    bool playerNearNPC();

private:
    void buildScene();
    void handleCollisions();
    void updateCamera();

    void loadFromFile(std::string filename);

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
    EventQueue& mEventQueue;

    SceneNode mSceneGraph;
    std::array<SceneNode*, LayerCount> mSceneLayers;
    CommandQueue mCommandQueue;
    
    bool mIsNearNPC = false;

    b2World& mWorld;
    float mBoxScale;
    float mGameScale;

    MapManager mMapLoader;

    Player* mPlayer;
    sf::Vector2f mPlayerPos;
    sf::Vector2f mStartPos;
    sf::Vector2f mEntryPos;
    
    sf::Sprite mHeartSprite;
    sf::Sprite mCoinSprite;
    GUI::Label mCoinLabel;
    int mCoinCollected;

};
