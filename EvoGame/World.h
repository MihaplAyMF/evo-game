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

//struct Object
//{
//    int GetPropertyInt(std::string name);
//    float GetPropertyFloat(std::string name);
//    std::string GetPropertyString(std::string name);
//
//    std::string name;
//    std::string type;
//    std::map<std::string, std::string> properties;
//    sf::Rect<int> rect;
//
//    sf::Sprite sprite;
//};

class World : public sf::NonCopyable
{
public:

    explicit World(sf::RenderWindow& window, FontHolder& fonts);
    
    void update(sf::Time dt);
    void draw();

    CommandQueue& getCommandQueue();

    bool LoadFromFile(std::string filename);
    //Object GetObject(std::string name);
    //std::vector<Object> GetObjects(std::string name);
    //sf::Vector2i GetTileSize();

private:
    void loadTextures();
    void buildScene();

    enum Layer
    {
        Background,
        Air,
        LayerCount
    };

private:
    sf::RenderTarget& mTarget;
    sf::RenderTexture mSceneTexture;
    //sf::View						   mWorldView;
    TextureHolder mTextures;
    FontHolder& mFonts;

    SceneNode mSceneGraph;
    std::array<SceneNode*, LayerCount> mSceneLayers;
    CommandQueue mCommandQueue;

    Player* mPlayer;


    int width, height, tileWidth, tileHeight;
    int firstTileID;

};