#include <tinyxml2.h>
#include <fstream>

#include "DataTables.h"
#include "SpriteNode.h"
#include "Settings.h"
#include "World.h"
#include "Block.h"
#include "Coin.h"
#include "Ladder.h"
#include "Exit.h"

#include <iostream>

extern const float boxScale;
extern const float gameScale;

sf::Vector2u res = Settings::getInstance().getCurrentResolution();
const float zoomValue = 1.2;

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
    : mWorldView(sf::FloatRect({0, 0}, {window.getSize().x / zoomValue, window.getSize().y / zoomValue}))
    , mHUDView(window.getDefaultView())
    , mTarget(window)
    , mFonts(fonts)
    , mTextures(texture)
    , mWorld(getWorld())
    , mPlayer(nullptr)
    , mGlobalPos(0, 0)
    , mPlayerPos(0, 0)
    , mCoinLabel("", mFonts)
    , mCoinCollected(0)
    , mHeartSprite(mTextures.get(Textures::Tileset))
    , mCoinSprite(mTextures.get(Textures::Tileset))
{
    std::cout << res.x << ", " << res.y << std::endl;

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

    playerUpdate();
    handleCollisions();
    updateCamera();
    
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
    for(std::size_t i = 0; i < LayerCount; ++i)
    {
        if(mSceneLayers[i] != nullptr)
        {
            mSceneLayers[i]->cleanup();
        }
    }

    b2Body* body = mWorld.GetBodyList();
    while(body != nullptr)                                                      
    {
        b2Body* nextBody = body->GetNext(); 
        mWorld.DestroyBody(body); 
        body = nextBody;
    }
}

void World::saveFirstGameState()
{
    const std::string& filename = "binary.bin";

    std::ofstream saveFile(filename, std::ios::binary);
    if(!saveFile.is_open())
    {
        //std::cerr << "Failed to open save file." << std::endl;
        return;
    }

    mGlobalPos = sf::Vector2f(0, 0);
    mPlayerPos = sf::Vector2f(0, 0);
    mCurrentMap = "Media/Map/Map1.tmx";

    saveFile.write(reinterpret_cast<const char*>(&mGlobalPos.x), sizeof(mGlobalPos.x));
    saveFile.write(reinterpret_cast<const char*>(&mGlobalPos.y), sizeof(mGlobalPos.y));

    saveFile.write(reinterpret_cast<const char*>(&mPlayerPos.x), sizeof(mPlayerPos.x));
    saveFile.write(reinterpret_cast<const char*>(&mPlayerPos.y), sizeof(mPlayerPos.y));
    
    size_t length = mCurrentMap.size();
    saveFile.write(reinterpret_cast<const char*>(&length), sizeof(length));
    saveFile.write(mCurrentMap.c_str(), length);

    saveFile.close();
}

bool World::loadFromFile(std::string filename)
{ 
    tinyxml2::XMLDocument levelFile;

    if(levelFile.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS)
    {
        //std::cerr << "Loading XML file \"" << filename << "\" failed." << std::endl;
        return false;
    }

    tinyxml2::XMLElement* map;
    map = levelFile.FirstChildElement("map");

    int width, height, tileWidth, tileHeight, firstTileID;

    map->QueryIntAttribute("width", &width);
    map->QueryIntAttribute("height", &height);
    map->QueryIntAttribute("tilewidth", &tileWidth);
    map->QueryIntAttribute("tileheight", &tileHeight);

    tinyxml2::XMLElement* tilesetElement;
    tilesetElement = map->FirstChildElement("tileset");
    tilesetElement->QueryIntAttribute("firstgid", &firstTileID);

    int columns = mTextures.get(Textures::Tileset).getSize().x / tileWidth;
    int rows = mTextures.get(Textures::Tileset).getSize().y / tileHeight;

    std::vector<sf::IntRect> subRects;
    
    for(int y = 0; y < rows; y++)
        for(int x = 0; x < columns; x++)
        {
            sf::IntRect rect;

            rect.position = {x * tileWidth, y * tileHeight}; 
            rect.size = {tileWidth, tileHeight};

            subRects.push_back(rect);
        }

    tinyxml2::XMLElement* layerElement;
    layerElement = map->FirstChildElement("layer");
    while(layerElement)
    {

        tinyxml2::XMLElement* layerDataElement;
        layerDataElement = layerElement->FirstChildElement("data");

        tinyxml2::XMLElement* tileElement;
        tileElement = layerDataElement->FirstChildElement("tile");

        if(tileElement == NULL)
        {
            //std::cout << "Bad map. No tile information found." << std::endl;
            return false;
        }

        int x = 0;
        int y = 0;

        while(tileElement)
        {
            int tileGID;
            const char* gidAttr = tileElement->Attribute("gid");
            if(gidAttr)
            {
                tileGID = atoi(gidAttr);
            }
            else
            {
                tileGID = 0;
            }
            int subRectToUse = tileGID - firstTileID;

            if(subRectToUse >= 0)
            {
                sf::Texture& spriteTexture = mTextures.get(Textures::Tileset);
                std::unique_ptr<SpriteNode> finishSprite(new SpriteNode(spriteTexture));
                finishSprite->setTextureRect(subRects[subRectToUse]);
                finishSprite->setScale({gameScale, gameScale});
                finishSprite->setPosition({x * tileWidth * gameScale, y * tileHeight * gameScale});
                finishSprite->setBackground(true);
                mSceneLayers[Background]->attachChild(std::move(finishSprite));
            }

            tileElement = tileElement->NextSiblingElement("tile");

            x++;
            if(x >= width)
            {
                x = 0;
                y++;
                if(y >= height)
                    y = 0;
            }
        }

        layerElement = layerElement->NextSiblingElement("layer");
    }

    tinyxml2::XMLElement* objectGroupElement;

    if(map->FirstChildElement("objectgroup") != NULL)
    {
        objectGroupElement = map->FirstChildElement("objectgroup");
        while(objectGroupElement)
        {
            tinyxml2::XMLElement* objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");
            
            while(objectElement)
            {
                std::string objectType;
                if(objectElement->Attribute("type") != NULL)
                {
                    objectType = objectElement->Attribute("type");
                }
                std::string objectName;
                if(objectElement->Attribute("name") != NULL)
                {
                    objectName = objectElement->Attribute("name");
                }
                int objectID = atoi(objectElement->Attribute("id"));
                
                int x = atoi(objectElement->Attribute("x"));
                int y = atoi(objectElement->Attribute("y"));

                int width, height;

                if(objectElement->Attribute("width") != NULL)
                {
                    width = atoi(objectElement->Attribute("width"));
                    height = atoi(objectElement->Attribute("height"));
                }
                else
                {
                    width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].size.x;
                    height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].size.y;
                }

                sf::FloatRect rect;
                
                rect.position = {x * gameScale, y * gameScale};
                rect.size = {width * gameScale, height * gameScale};

                if(objectName == "player")
                {
                    mStartPos = sf::Vector2f({rect.position.x, rect.position.y - rect.size.y});
                    rect.position  = {mPlayerPos.x, mPlayerPos.y};

                    int tileGID;
                    const char* gidAttr = objectElement->Attribute("gid");
                    if(gidAttr)
                    {
                        tileGID = atoi(gidAttr);
                    }
                    else
                    {
                        tileGID = 0;
                    }
                    int subRectToUse = tileGID - firstTileID;

                    std::unique_ptr<Player> player = std::make_unique<Player>(Player::FriedlyPlayer, mTextures, rect);
                    mPlayer = player.get();
                    mPlayer->setTextureRect(subRects[subRectToUse]);
                    mSceneLayers[Air]->attachChild(std::move(player));
                }
                else if(objectName == "block") 
                {
                    sf::Vector2i tileSize(tileWidth * gameScale, tileHeight * gameScale);

                    std::unique_ptr<Block> block = std::make_unique<Block>(rect, tileSize);
                    mSceneLayers[Air]->attachChild(std::move(block));
                }
                else if(objectName == "coin")
                {
                    auto& coins = mCoinIDCollected[mCurrentMap];
                    if(coins.find(objectID) == coins.end())
                    {
                        std::unique_ptr<Coin> coin = std::make_unique<Coin>(mTextures, objectID, rect);
                        mSceneLayers[Air]->attachChild(std::move(coin));
                    }
                }
                else if(objectName == "ladder")
                {
                    std::unique_ptr<Ladder> ladder = std::make_unique<Ladder>(rect);
                    mSceneLayers[Air]->attachChild(std::move(ladder));
                }
                else if(objectName == "exit")
                {
                    std::unique_ptr<Exit> exit = std::make_unique<Exit>(rect);
                    mSceneLayers[Air]->attachChild(std::move(exit));
                }
                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    }    
    return true;
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

    loadFromFile(mCurrentMap);
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
            
            mCoinIDCollected[mCurrentMap].insert(coin.getObjectID());
            coin.remove();
            mCoinCollected++;
            mCoinLabel.setText(std::to_string(mCoinCollected));
        }
        else if(matchesCategories(pair, Category::Player, Category::Ladder))
        {
            mPlayer->setIsLadder(true);
        }
        else if(matchesCategories(pair, Category::Player, Category::Exit))
        {
            if(mPlayer->getIsExit() == true)
            {
               if(mGlobalPos == sf::Vector2f(0, 0))
               {
                   mGlobalPos.x -= 1;
                   mCurrentMap = "Media/Map/Map0.tmx";
                   switchMap(mCurrentMap);
               }
            }
        }
    }
}

void World::updateCamera()
{
    b2Body* body = mPlayer->getBodyObject();

    sf::Vector2f pos(body->GetPosition().x, body->GetPosition().y);
    sf::Vector2f size(mPlayer->getBoundingRect().position);
    sf::Vector2f scaledPos(pos.x * boxScale, pos.y * boxScale);

    mPlayer->setPosition({scaledPos.x, scaledPos.y});

    sf::Vector2f halfWindowSize = sf::Vector2f(mWorldView.getSize().x / 2.0f, mWorldView.getSize().y / 2.0f);
    sf::Vector2f newCenter = scaledPos + sf::Vector2f(size.x / 2, size.y / 2);

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
    mCoinLabel.setText(std::to_string(mCoinCollected));
    mCoinLabel.getText().setFillColor(sf::Color::Black);
    mCoinLabel.getText().setCharacterSize(25);
    mCoinLabel.setPosition({64, 64});
    
    mHeartSprite.setTextureRect(sf::IntRect({96, 112}, {16, 16}));
    mHeartSprite.setScale({gameScale * zoomValue, gameScale * zoomValue});
    mHeartSprite.setPosition({16, 16});

    mCoinSprite.setTextureRect(sf::IntRect({80, 112}, {16, 16}));
    mCoinSprite.setScale({gameScale * zoomValue, gameScale * zoomValue});
    mCoinSprite.setPosition({16, 48});
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
    mPlayer->setIsExit(false);
    mPlayer->setIsLadder(false);
}

void World::saveGameState()
{
    const std::string& filename = "binary.bin";

    std::ofstream saveFile(filename, std::ios::binary);
    if(!saveFile.is_open())
    {
        //std::cerr << "Failed to open save file." << std::endl;
        return;
    }
    
    if(mPlayer == nullptr)
        return;

    // Save player state    
    
    saveFile.write(reinterpret_cast<const char*>(&mGlobalPos.x), sizeof(mGlobalPos.x));
    saveFile.write(reinterpret_cast<const char*>(&mGlobalPos.y), sizeof(mGlobalPos.y));

    saveFile.write(reinterpret_cast<const char*>(&mPlayerPos.x), sizeof(mPlayerPos.x));
    saveFile.write(reinterpret_cast<const char*>(&mPlayerPos.y), sizeof(mPlayerPos.y));

    size_t length = mCurrentMap.size();
    saveFile.write(reinterpret_cast<const char*>(&length), sizeof(length));
    saveFile.write(mCurrentMap.c_str(), length);
    // Save other game state as needed

    saveFile.close();
}

void World::loadGameState()
{
    const std::string& filename = "binary.bin";

    std::ifstream loadFile(filename, std::ios::binary);
    if(!loadFile)
    {
        //std::cerr << "Save file not found. Creating a new one." << std::endl;
        saveFirstGameState();
        return;
    }

    loadFile.read(reinterpret_cast<char*>(&mGlobalPos.x), sizeof(mGlobalPos.x));
    loadFile.read(reinterpret_cast<char*>(&mGlobalPos.y), sizeof(mGlobalPos.y));

    loadFile.read(reinterpret_cast<char*>(&mPlayerPos.x), sizeof(mPlayerPos.x));
    loadFile.read(reinterpret_cast<char*>(&mPlayerPos.y), sizeof(mPlayerPos.y));

    size_t length;
    loadFile.read(reinterpret_cast<char*>(&length), sizeof(length));

    char* buffer = new char[length + 1];
    loadFile.read(buffer, length);
    buffer[length] = '\0';

    mCurrentMap = buffer;
    delete[] buffer;

    loadFile.close();
}

void World::switchMap(const std::string& filename)
{
    saveGameState();
    cleanup();
    loadGameState();
    loadFromFile(filename);
}

void World::changeMapPlayerOutsideView()
{
    auto gameBounds = getEvoGameBounds();
    auto playerBounds = mPlayer->getBoundingRect();
    
    mPlayerPos = sf::Vector2f(playerBounds.position.x, playerBounds.position.y + playerBounds.size.y);

    if(playerBounds.position.x > gameBounds.position.x + gameBounds.size.x) 
    {
        if(mGlobalPos == sf::Vector2f(0, 0))
        {
            mGlobalPos.x += 1;
            mPlayerPos = sf::Vector2f(gameBounds.position.x, playerBounds.position.y + playerBounds.size.y); 
            mCurrentMap = "Media/Map/Map2.tmx";
            switchMap(mCurrentMap);
        }
        else if(mGlobalPos == sf::Vector2f(1, 0))
        {
            mGlobalPos.x += 1;
            mPlayerPos = sf::Vector2f(gameBounds.position.x, playerBounds.position.y + playerBounds.size.y); 
            mCurrentMap = "Media/Map/Map3.tmx";
            switchMap(mCurrentMap);
        }
    }
    else if(playerBounds.position.x + playerBounds.size.x < gameBounds.position.x) 
    {
        if(mGlobalPos == sf::Vector2f(-1, 0))
        {
            mGlobalPos.x += 1;
            mPlayerPos = sf::Vector2f(gameBounds.position.x, playerBounds.position.y + playerBounds.size.y);
            mCurrentMap = "Media/Map/Map1.tmx";
            switchMap(mCurrentMap);
        }
        else if(mGlobalPos == sf::Vector2f(1, 0))
        {
            mGlobalPos.x -= 1;
            mPlayerPos = sf::Vector2f(gameBounds.size.x - playerBounds.size.x, playerBounds.position.y + playerBounds.size.y); 
            mCurrentMap = "Media/Map/Map1.tmx";
            switchMap(mCurrentMap);
        }  
        else if(mGlobalPos == sf::Vector2f(2, 0))
        {
            mGlobalPos.x -= 1;
            mPlayerPos = sf::Vector2f(gameBounds.size.x - playerBounds.size.x, playerBounds.position.y + playerBounds.size.y); 
            mCurrentMap = "Media/Map/Map2.tmx";
            switchMap(mCurrentMap);
        }
    }
    else if(playerBounds.position.y + playerBounds.size.y > gameBounds.position.y + gameBounds.size.y)
    {
        mPlayer->setPos(mStartPos);
    }
}

bool World::hasAlivePlayer()
{    
    return true;
}

sf::FloatRect World::getViewBounds() const
{
    return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}

sf::FloatRect World::getEvoGameBounds() const
{
    return sf::FloatRect({0.f, 0.f}, {static_cast<float>(res.x), static_cast<float>(res.y)});
}

