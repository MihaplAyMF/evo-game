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

private:
    bool parseMapAttributes(tinyxml2::XMLElement* map, MapInfo& mapInfo);
    void generateSubRects(MapInfo& mapInfo);
    void parseLayers(tinyxml2::XMLElement* map, MapInfo& mapInfo, std::array<SceneNode*, LayerCount>& sceneLayers);
    void parseObjects(tinyxml2::XMLElement* map, MapInfo& mapInfo, std::array<SceneNode*, LayerCount>&  sceneLayers, sf::Vector2f& startPos);

    TextureHolder& mTextures;
    float mGameScale;
};

