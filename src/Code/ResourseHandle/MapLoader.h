#pragma once

#include <string>
#include <vector>
#include <tinyxml2.h>

#include "ResourceIdentifiers.h"
#include "SceneNode.h"

struct MapInfo {
    int width = 0;
    int height = 0;
    int tileWidth = 0;
    int tileHeight = 0;
    int firstTileID = 0;
    std::vector<sf::IntRect> subRects;
};

enum Layer
{
    Background,
    Air,
    LayerCount
};

class MapLoader 
{
public:
    explicit MapLoader(TextureHolder& textures);
    bool loadFromFile(const std::string& filename, std::array<SceneNode*, LayerCount>& sceneLayers, sf::Vector2f& startPos);
    std::map<std::string, std::set<int>>& getCollectedCoins();

    void setCurrentMap(const std::string& mapName);
    const std::string& getCurrentMap() const;
    
    void setPlayerHP(const int HP);
    const int& getPlayerHP() const;

private:
    bool parseMapAttributes(tinyxml2::XMLElement* map);
    void generateSubRects();
    void parseLayers(tinyxml2::XMLElement* map, std::array<SceneNode*, LayerCount>& sceneLayers);
    void parseObjects(tinyxml2::XMLElement* map, std::array<SceneNode*, LayerCount>&  sceneLayers, sf::Vector2f& startPos);
 
    TextureHolder& mTextures;
    float mGameScale;
    std::string mCurrentMap;
    std::map<std::string, std::set<int>> mCoinIDCollected;
    int mPlayerHP;
    MapInfo mMapInfo;
};

