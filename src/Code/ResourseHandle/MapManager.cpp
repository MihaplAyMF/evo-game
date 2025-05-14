#include "MapManager.h"
#include "SpriteNode.h"
#include "Transition.h"
#include "Settings.h"
#include "Coin.h"
#include "Ladder.h"
#include "Block.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

struct Portal 
{
    sf::FloatRect portalRect;
    sf::Vector2f startPos;
    std::string mapName;
};

MapManager::MapManager(TextureHolder& textures) 
    : mTextures(textures)
    , mGameScale(Settings::getInstance().getScale())
{ }

#include <iostream>

bool MapManager::loadFromFile(const std::string& filename, std::array<SceneNode*, LayerCount>& sceneLayers, sf::Vector2f& startPos)
{
    std::cout << filename << std::endl;

    tinyxml2::XMLDocument levelFile;
    if (levelFile.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS) {
        return false;
    }

    tinyxml2::XMLElement* map = levelFile.FirstChildElement("map");
    if (!map) return false;
    if (!parseMapAttributes(map)) return false;
    
    generateSubRects();
    parseLayers(map, sceneLayers);
    parseObjects(map, sceneLayers, startPos);

    return true;
}

std::map<std::string, std::set<int>>& MapManager::getCollectedCoins() 
{
    return mCoinIDCollected;
}

sf::Vector2f MapManager::getMapSize()
{
    return {mMapInfo.mapWidth, mMapInfo.mapHeight};
}

void MapManager::setCurrentMap(const std::string& mapName) 
{
    mCurrentMap = mapName;
}

const std::string& MapManager::getCurrentMap() const 
{
    return mCurrentMap;
}

bool MapManager::parseMapAttributes(tinyxml2::XMLElement* map) {
    map->QueryIntAttribute("width", &mMapInfo.width);
    map->QueryIntAttribute("height", &mMapInfo.height);
    map->QueryIntAttribute("tilewidth", &mMapInfo.tileWidth);
    map->QueryIntAttribute("tileheight", &mMapInfo.tileHeight);
    
    mMapInfo.mapWidth = mMapInfo.tileWidth * mMapInfo.width * mGameScale;
    mMapInfo.mapHeight = mMapInfo.tileHeight * mMapInfo.height * mGameScale;

    tinyxml2::XMLElement* tilesetElement = map->FirstChildElement("tileset");
    if (!tilesetElement) return false;

    tilesetElement->QueryIntAttribute("firstgid", &mMapInfo.firstTileID);
    return true;
}

void MapManager::generateSubRects() {
    int columns = mTextures.get(Textures::Tileset).getSize().x / mMapInfo.tileWidth;
    int rows = mTextures.get(Textures::Tileset).getSize().y / mMapInfo.tileHeight;

    for (int y = 0; y < rows; y++)
        for (int x = 0; x < columns; x++)
        {
            sf::IntRect rect;

            rect.position = {x * mMapInfo.tileWidth, y * mMapInfo.tileHeight}; 
            rect.size = {mMapInfo.tileWidth, mMapInfo.tileHeight};

            mMapInfo.subRects.push_back(rect);
        }
}

void MapManager::parseLayers(tinyxml2::XMLElement* map, std::array<SceneNode*, LayerCount>&  sceneLayers) {
    tinyxml2::XMLElement* layerElement = map->FirstChildElement("layer");
    while (layerElement) {
        tinyxml2::XMLElement* layerDataElement = layerElement->FirstChildElement("data");
        tinyxml2::XMLElement* tileElement = layerDataElement->FirstChildElement("tile");

        int x = 0, y = 0;
        while (tileElement) {
            int tileGID = tileElement->IntAttribute("gid", 0);
            int subRectToUse = tileGID - mMapInfo.firstTileID;

            if (subRectToUse >= 0) {
                sf::Texture& spriteTexture = mTextures.get(Textures::Tileset);
                auto sprite = std::make_unique<SpriteNode>(spriteTexture);
                sprite->setTextureRect(mMapInfo.subRects[subRectToUse]);
                sprite->setScale({mGameScale, mGameScale});
                sprite->setPosition({x * mMapInfo.tileWidth * mGameScale, y * mMapInfo.tileHeight * mGameScale});
                sprite->setBackground(true);
                sceneLayers[Background]->attachChild(std::move(sprite));
            }

            tileElement = tileElement->NextSiblingElement("tile");
            if (++x >= mMapInfo.width) {
                x = 0;
                if (++y >= mMapInfo.height) break;
            }
        }
        layerElement = layerElement->NextSiblingElement("layer");
    }
}

void MapManager::parseObjects(tinyxml2::XMLElement* map, std::array<SceneNode*, LayerCount>& sceneLayers, sf::Vector2f& startPos) {
    tinyxml2::XMLElement* objectGroupElement = map->FirstChildElement("objectgroup");
    while (objectGroupElement) {
        tinyxml2::XMLElement* objectElement = objectGroupElement->FirstChildElement("object");

        while (objectElement) {
            std::string objectName = objectElement->Attribute("name") ? objectElement->Attribute("name") : "";
            int x = objectElement->IntAttribute("x");
            int y = objectElement->IntAttribute("y");
            int width = objectElement->IntAttribute("width", mMapInfo.tileWidth);
            int height = objectElement->IntAttribute("height", mMapInfo.tileHeight);
        

            sf::FloatRect rect({x * mGameScale, y * mGameScale}, {width * mGameScale, height * mGameScale});

            if (objectName == "player") 
            {
                startPos = {rect.position.x, rect.position.y - rect.size.y};
            } 
            else if (objectName == "block") 
            {
                auto block = std::make_unique<Block>(rect, sf::Vector2i(mMapInfo.tileWidth * mGameScale, mMapInfo.tileHeight * mGameScale));
                sceneLayers[Air]->attachChild(std::move(block));
            } 
            else if (objectName == "coin") 
            {
                auto& coins = mCoinIDCollected[mCurrentMap];
 
                if(coins.find(objectElement->IntAttribute("id")) == coins.end())
                {
                    std::unique_ptr<Coin> coin = std::make_unique<Coin>(mTextures, objectElement->IntAttribute("id"), rect);
                    sceneLayers[Air]->attachChild(std::move(coin));
                }
            } 
            else if (objectName == "ladder") 
            {
                auto ladder = std::make_unique<Ladder>(rect);
                sceneLayers[Air]->attachChild(std::move(ladder));
            }
            else if (objectName == "transition")
            {
                std::string mapName = (objectElement->FirstChildElement("properties")) ?
                    objectElement->FirstChildElement("properties")->FirstChildElement("property")->Attribute("value") : "";
                
                sf::FloatRect mapBounds({0, 0}, {1920, 1080});
                
                bool isEntry = !( 
                       rect.position.x <= 0.f
                    || rect.position.y <= 0.f
                    || rect.position.x + rect.size.x >= mapBounds.size.x
                    || rect.position.y + rect.size.y >= mapBounds.size.y);
            
                auto transition = std::make_unique<Transition>(rect, mapName, isEntry); 
                sceneLayers[Air]->attachChild(std::move(transition));
            }
            objectElement = objectElement->NextSiblingElement("object");
        }

        objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
    }
}
