#include "MapLoader.h"
#include "SpriteNode.h"
#include "Settings.h"
#include "Coin.h"
#include "Ladder.h"
#include "Entry.h"
#include "Block.h"

#include <iostream>

MapLoader::MapLoader(TextureHolder& textures) 
    : mTextures(textures)
    , mGameScale(Settings::getInstance().getScale())
{ }

bool MapLoader::loadFromFile(const std::string& filename, std::array<SceneNode*, LayerCount>& sceneLayers, sf::Vector2f& startPos)
{
    tinyxml2::XMLDocument levelFile;
    if (levelFile.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS) {
        return false;
    }

    tinyxml2::XMLElement* map = levelFile.FirstChildElement("map");
    if (!map) return false;

    MapInfo mapInfo;
    if (!parseMapAttributes(map, mapInfo)) return false;
    
    generateSubRects(mapInfo);
    parseLayers(map, mapInfo, sceneLayers);
    parseObjects(map, mapInfo, sceneLayers, startPos);

    return true;
}

std::map<std::string, std::set<int>>& MapLoader::getCollectedCoins() 
{
    return mCoinIDCollected;
}

void MapLoader::setCurrentMap(const std::string& mapName) 
{
    mCurrentMap = mapName;
}

const std::string& MapLoader::getCurrentMap() const 
{
    return mCurrentMap;
}

void MapLoader::setPlayerHP(const int HP)
{
    mPlayerHP = HP;
}

const int& MapLoader::getPlayerHP() const 
{
    return mPlayerHP;
}


bool MapLoader::parseMapAttributes(tinyxml2::XMLElement* map, MapInfo& mapInfo) {
    map->QueryIntAttribute("width", &mapInfo.width);
    map->QueryIntAttribute("height", &mapInfo.height);
    map->QueryIntAttribute("tilewidth", &mapInfo.tileWidth);
    map->QueryIntAttribute("tileheight", &mapInfo.tileHeight);
    
    std::cout << mapInfo.tileWidth << ", " << mapInfo.tileHeight << std::endl;

    tinyxml2::XMLElement* tilesetElement = map->FirstChildElement("tileset");
    if (!tilesetElement) return false;

    tilesetElement->QueryIntAttribute("firstgid", &mapInfo.firstTileID);
    return true;
}

void MapLoader::generateSubRects(MapInfo& mapInfo) {
    int columns = mTextures.get(Textures::Tileset).getSize().x / mapInfo.tileWidth;
    int rows = mTextures.get(Textures::Tileset).getSize().y / mapInfo.tileHeight;

    for (int y = 0; y < rows; y++)
        for (int x = 0; x < columns; x++)
        {
            sf::IntRect rect;

            rect.position = {x * mapInfo.tileWidth, y * mapInfo.tileHeight}; 
            rect.size = {mapInfo.tileWidth, mapInfo.tileHeight};

            mapInfo.subRects.push_back(rect);
        }
}

void MapLoader::parseLayers(tinyxml2::XMLElement* map, MapInfo& mapInfo, std::array<SceneNode*, LayerCount>&  sceneLayers) {
    tinyxml2::XMLElement* layerElement = map->FirstChildElement("layer");
    while (layerElement) {
        tinyxml2::XMLElement* layerDataElement = layerElement->FirstChildElement("data");
        tinyxml2::XMLElement* tileElement = layerDataElement->FirstChildElement("tile");

        int x = 0, y = 0;
        while (tileElement) {
            int tileGID = tileElement->IntAttribute("gid", 0);
            int subRectToUse = tileGID - mapInfo.firstTileID;

            if (subRectToUse >= 0) {
                sf::Texture& spriteTexture = mTextures.get(Textures::Tileset);
                auto sprite = std::make_unique<SpriteNode>(spriteTexture);
                sprite->setTextureRect(mapInfo.subRects[subRectToUse]);
                sprite->setScale({mGameScale, mGameScale});
                sprite->setPosition({x * mapInfo.tileWidth * mGameScale, y * mapInfo.tileHeight * mGameScale});
                sprite->setBackground(true);
                sceneLayers[Background]->attachChild(std::move(sprite));
            }

            tileElement = tileElement->NextSiblingElement("tile");
            if (++x >= mapInfo.width) {
                x = 0;
                if (++y >= mapInfo.height) break;
            }
        }
        layerElement = layerElement->NextSiblingElement("layer");
    }
}

void MapLoader::parseObjects(tinyxml2::XMLElement* map, MapInfo& mapInfo, std::array<SceneNode*, LayerCount>& sceneLayers, sf::Vector2f& startPos) {
    tinyxml2::XMLElement* objectGroupElement = map->FirstChildElement("objectgroup");
    while (objectGroupElement) {
        tinyxml2::XMLElement* objectElement = objectGroupElement->FirstChildElement("object");

        while (objectElement) {
            std::string objectName = objectElement->Attribute("name") ? objectElement->Attribute("name") : "";
            int x = objectElement->IntAttribute("x");
            int y = objectElement->IntAttribute("y");
            int width = objectElement->IntAttribute("width", mapInfo.tileWidth);
            int height = objectElement->IntAttribute("height", mapInfo.tileHeight);
        
            sf::FloatRect rect({x * mGameScale, y * mGameScale}, {width * mGameScale, height * mGameScale});

            if (objectName == "player") 
            {
                startPos = {rect.position.x, rect.position.y - rect.size.y};
            } 
            else if (objectName == "block") 
            {
                auto block = std::make_unique<Block>(rect, sf::Vector2i(mapInfo.tileWidth * mGameScale, mapInfo.tileHeight * mGameScale));
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
            else if (objectName == "entry")
            {
                auto ladder = std::make_unique<Entry>(rect);
                sceneLayers[Air]->attachChild(std::move(ladder));
            }

            objectElement = objectElement->NextSiblingElement("object");
        }

        objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
    }
}



