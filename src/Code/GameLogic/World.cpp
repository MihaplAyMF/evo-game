#include <SFML/System/Vector2.hpp>
#include <string>
#include <tinyxml2.h>
#include <fstream>

#include <iostream>

#include "Category.h"
#include "DataTables.h"
#include "Settings.h"
#include "Transition.h"
#include "World.h"
#include "Coin.h"

const float zoomValue = 1.3;

bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
{
    unsigned int category1 = colliders.first->getCategory();
    unsigned int category2 = colliders.second->getCategory();

    if(type1 & category1 && type2 & category2)
    {
        return true;
    }
    else if(type1 & category2 && type2 & category1) 
    {
        std::swap(colliders.first, colliders.second);
        return true;
    }
    else
    {
        return false;
    }
}

World::World(sf::RenderWindow& window, TextureHolder& texture, FontHolder& fonts)
    : mWorldView(sf::FloatRect({0, 0}, {1920.f / zoomValue, 1080.f / zoomValue}))
    , mHUDView(window.getDefaultView())
    , mTarget(window)
    , mFonts(fonts)
    , mTextures(texture)
    , mMapLoader(mTextures)
    , mWorld(getWorld())
    , mBoxScale(getBoxScale())
    , mGameScale(Settings::getInstance().getScale())
    , mPlayer(nullptr)
    , mPlayerPos(0, 0)
    , mCoinLabel("", mFonts)
    , mCoinCollected(0)
    , mHeartSprite(mTextures.get(Textures::Tileset))
    , mCoinSprite(mTextures.get(Textures::Tileset))
{
    loadGameState();
    createHUD();
    buildScene();
}

void World::update(sf::Time dt)
{
    mWorld.Step(1 / 60.f, 8, 3);
    changeMapPlayerOutsideView();

    while(!mCommandQueue.isEmpty())
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);

    mSceneGraph.removeWrecks();
    
    mPlayer->setIsLadder(false);
    updateCamera();
    handleCollisions();
    mPlayer->setIsEntry(false);
    
    mSceneGraph.update(dt, mCommandQueue);
}

void World::draw()
{
    mTarget.setView(mWorldView);
    mTarget.draw(mSceneGraph);
    
    drawHUD();
}

CommandQueue& World::getCommandQueue()
{
    return mCommandQueue;
}

void World::clean()
{
    saveGameState();
    cleanup();
}

void World::cleanup()
{
    for (std::size_t i = 0; i < LayerCount; ++i) 
    {
        if (mSceneLayers[i] != nullptr) 
        {
            mSceneLayers[i]->cleanup();
        }
    }

    b2Body* body = mWorld.GetBodyList();
    b2Body* playerBody = mPlayer->getBodyObject();

    while (body != nullptr) 
    {
        b2Body* nextBody = body->GetNext();
        if (body != playerBody) 
        {
            mWorld.DestroyBody(body);
        }
        body = nextBody;
    }
}

void World::saveFirstGameState()
{
    const std::string& filename = "binary.bin";

    std::ofstream saveFile(filename, std::ios::binary);
    if(!saveFile.is_open())
        return;

    mPlayerPos = sf::Vector2f(128, 385);
    mMapLoader.setCurrentMap("Media/Map/Map1.tmx");

    saveFile.write(reinterpret_cast<const char*>(&mPlayerPos.x), sizeof(mPlayerPos.x));
    saveFile.write(reinterpret_cast<const char*>(&mPlayerPos.y), sizeof(mPlayerPos.y));
    
    size_t length = mMapLoader.getCurrentMap().size();
    saveFile.write(reinterpret_cast<const char*>(&length), sizeof(length));
    saveFile.write(mMapLoader.getCurrentMap().c_str(), length);

    saveFile.close();
}

void World::buildScene()
{
    for(std::size_t i = 0; i < LayerCount; ++i)
    {
        Category::Type category = (i == Air) ? Category::SceneAirLayer : Category::None;

        SceneNode::Ptr layer(new SceneNode(category));
        mSceneLayers[i] = layer.get();

        mSceneGraph.attachChild(std::move(layer));
    }

    mMapLoader.loadFromFile(mMapLoader.getCurrentMap(), mSceneLayers, mStartPos);

    sf::FloatRect rect;
    rect.position = {mPlayerPos.x, mPlayerPos.y};
    rect.size = {16 * mGameScale, 16 * mGameScale}; // 16 - is the tile widht and height

    std::unique_ptr<Player> player = std::make_unique<Player>(Player::FriedlyPlayer, mTextures, rect);
    mPlayer = player.get();
    mPlayer->setPosition(mStartPos);
    mSceneLayers[Air]->attachChild(std::move(player));
}

void World::handleCollisions()
{
    std::set<SceneNode::Pair> colisionPairs;
    mSceneGraph.checkSceneCollision(mSceneGraph, colisionPairs);
    
    for(SceneNode::Pair pair : colisionPairs)
    {
        if(matchesCategories(pair, Category::Player, Category::Coin))
        {
            auto& coin = dynamic_cast<Coin&>(*pair.second);
            
            mMapLoader.getCollectedCoins()[mMapLoader.getCurrentMap()].insert(coin.getObjectID());
            coin.remove();
            mCoinCollected++;
            mCoinLabel.setText(std::to_string(mCoinCollected));
        }
        else if(matchesCategories(pair, Category::Player, Category::Ladder))
        {
            mPlayer->setIsLadder(true);
        }
        else if(matchesCategories(pair, Category::Player, Category::Transition))
        {
            auto& transition = dynamic_cast<Transition&>(*pair.second);

            sf::Vector2f gameSize = mMapLoader.getMapSize(); 
            auto playerBounds = mPlayer->getBoundingRect();
    
            mPlayerPos = sf::Vector2f(playerBounds.position.x, playerBounds.position.y + playerBounds.size.y);
       

            if(mPlayerPos.x > gameSize.x - playerBounds.size.x)
            {
                mMapLoader.setCurrentMap("Media/Map/" + transition.getMapName());
                switchMap(mMapLoader.getCurrentMap());
                mPlayer->setPos(sf::Vector2f(0, playerBounds.position.y)); 
            }
            else if(playerBounds.position.x < 0) 
            {
                mMapLoader.setCurrentMap("Media/Map/" + transition.getMapName());
                switchMap(mMapLoader.getCurrentMap());
                mPlayer->setPos(sf::Vector2f(gameSize.x - playerBounds.size.x, playerBounds.position.y)); 
            } 
            else if(mPlayer->getIsEntry() == true && transition.getIsEntry())
            {
                mMapLoader.setCurrentMap("Media/Map/" + transition.getMapName());
                switchMap(mMapLoader.getCurrentMap());
                mPlayer->setPos(transition.getPosition()); // UB - fixed later!!
            }
        }
    }
}

void World::updateCamera()
{
    b2Body* body = mPlayer->getBodyObject();
    sf::Vector2f pos(body->GetPosition().x, body->GetPosition().y);
    sf::Vector2f playerPos(pos.x * mBoxScale, pos.y * mBoxScale);
    sf::Vector2f size(mPlayer->getBoundingRect().position);
    mPlayer->setPosition({playerPos});

    sf::Vector2f halfWindowSize = sf::Vector2f(mWorldView.getSize().x / 2.0f, mWorldView.getSize().y / 2.0f);
    sf::Vector2f newCenter = playerPos;
    sf::Vector2f res = mMapLoader.getMapSize(); 


    if(newCenter.x - halfWindowSize.x < 0)
        newCenter.x = halfWindowSize.x;
    if(newCenter.y - halfWindowSize.y < 0)
        newCenter.y = halfWindowSize.y;
    if(newCenter.x + halfWindowSize.x > res.x)
        newCenter.x = res.x - halfWindowSize.x;
    if(newCenter.y + halfWindowSize.y > res.y)
        newCenter.y = res.y - halfWindowSize.y;

    mWorldView.setCenter(newCenter);
}

void World::createHUD()
{
    mCoinLabel.getText().setFillColor(sf::Color::Black);
    mCoinLabel.getText().setCharacterSize(35);    
    mCoinLabel.setPosition({110, 110});
    mCoinLabel.setText(std::to_string(mCoinCollected));
    
    mHeartSprite.setTextureRect(sf::IntRect({96, 112}, {16, 16}));
    mHeartSprite.setScale({mGameScale * zoomValue, mGameScale * zoomValue});
    mHeartSprite.setPosition({16, 32});

    mCoinSprite.setTextureRect(sf::IntRect({80, 112}, {16, 16}));
    mCoinSprite.setScale({mGameScale * zoomValue, mGameScale * zoomValue});
    mCoinSprite.setPosition({16, 80});
}

void World::drawHUD()
{
    mTarget.setView(mHUDView);

    for(int i = 0; i < mPlayer->getHitpoints(); ++i)
    {
        mHeartSprite.setPosition({16 + i * (mHeartSprite.getGlobalBounds().size.x - 5), 16}); 
        mTarget.draw(mHeartSprite);
    }

    mTarget.draw(mCoinSprite);
    mTarget.draw(mCoinLabel);
}

void World::playerUpdate()
{
    mPlayer->setIsEntry(false);
    mPlayer->setIsLadder(false);
}

void World::saveGameState()
{
    const std::string& filename = "binary.bin";

    std::ofstream saveFile(filename, std::ios::binary);
    if(!saveFile.is_open())
        return;
    
    if(mPlayer == nullptr)
        return;

    saveFile.write(reinterpret_cast<const char*>(&mPlayerPos.x), sizeof(mPlayerPos.x));
    saveFile.write(reinterpret_cast<const char*>(&mPlayerPos.y), sizeof(mPlayerPos.y));

    size_t length = mMapLoader.getCurrentMap().size();
    saveFile.write(reinterpret_cast<const char*>(&length), sizeof(length));
    saveFile.write(mMapLoader.getCurrentMap().c_str(), length);

    saveFile.close();
}

void World::loadGameState()
{
    const std::string& filename = "binary.bin";

    std::ifstream loadFile(filename, std::ios::binary);
    if(!loadFile)
    {
        saveFirstGameState();
        return;
    }

    loadFile.read(reinterpret_cast<char*>(&mPlayerPos.x), sizeof(mPlayerPos.x));
    loadFile.read(reinterpret_cast<char*>(&mPlayerPos.y), sizeof(mPlayerPos.y));

    size_t length;
    loadFile.read(reinterpret_cast<char*>(&length), sizeof(length));

    char* buffer = new char[length + 1];
    loadFile.read(buffer, length);
    buffer[length] = '\0';

    mMapLoader.setCurrentMap(buffer);
    delete[] buffer;

    loadFile.close();
}

void World::switchMap(const std::string& filename)
{ 
    saveGameState();
    cleanup();
    loadGameState();
   
    mMapLoader.loadFromFile(filename, mSceneLayers, mStartPos);
}

void World::changeMapPlayerOutsideView()
{
    sf::FloatRect gameBounds = {{0,0}, {mMapLoader.getMapSize().x, mMapLoader.getMapSize().y}};
    auto playerBounds = mPlayer->getBoundingRect();
    
    mPlayerPos = sf::Vector2f(playerBounds.position.x, playerBounds.position.y + playerBounds.size.y);

    if(playerBounds.position.y + playerBounds.size.y > gameBounds.position.y + gameBounds.size.y)
    {
        mPlayer->setPos(mStartPos);
        mPlayerPos = mStartPos;
        mPlayer->damage(1);
    }
}

bool World::hasAlivePlayer()
{   
    return mPlayer->getHitpoints() != 0;
}

sf::FloatRect World::getViewBounds() const
{
    return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}

sf::FloatRect World::getEvoGameBounds() const
{
    sf::Vector2u res = Settings::getInstance().getCurrentResolution();
    return sf::FloatRect({0.f, 0.f}, {static_cast<float>(res.x), static_cast<float>(res.y)});
}

