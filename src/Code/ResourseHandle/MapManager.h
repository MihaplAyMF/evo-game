#pragma once

#include <SFML/System/Vector2.hpp>
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
    float mapHeight = 0;
    float mapWidth = 0;
    int tilesetColumns = 0;
    std::vector<sf::IntRect> subRects;
};

enum Layer
{
    Background,
    Air,
    LayerCount
};

class MapManager 
{
public:
    explicit MapManager(TextureHolder& textures);
    bool loadFromFile(const std::string& filename, std::array<SceneNode*, LayerCount>& sceneLayers, sf::Vector2f& startPos);
    std::map<std::string, std::set<int>>& getCollectedCoins();
    sf::Vector2f getMapSize();

    void setCurrentMap(const std::string& mapName);
    const std::string& getCurrentMap() const;

private:
    bool parseMapAttributes(tinyxml2::XMLElement* map);
    void generateSubRects();
    void parseLayers(tinyxml2::XMLElement* map, std::array<SceneNode*, LayerCount>& sceneLayers);
    void parseObjects(tinyxml2::XMLElement* map, std::array<SceneNode*, LayerCount>&  sceneLayers, sf::Vector2f& startPos);
 
    TextureHolder& mTextures;
    float mGameScale;
    std::string mCurrentMap;
    std::map<std::string, std::set<int>> mCoinIDCollected;
    MapInfo mMapInfo;
};

