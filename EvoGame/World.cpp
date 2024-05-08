#include <iostream>
#include <tinyxml2.h>

#include "World.h"
#include "Block.h"

extern const float boxScale;
extern const float gameScale;
extern b2World world;

//int Object::GetPropertyInt(std::string name)
//{
//    return atoi(properties[name].c_str());
//}
//
//float Object::GetPropertyFloat(std::string name)
//{
//    return strtod(properties[name].c_str(), NULL);
//}
//
//std::string Object::GetPropertyString(std::string name)
//{
//    return properties[name];
//}

std::string getImagePath(std::string xmlFilePath)
{
    std::string imagePath;

    tinyxml2::XMLDocument doc;
    if(doc.LoadFile(xmlFilePath.c_str()) == tinyxml2::XML_SUCCESS)
    {
        tinyxml2::XMLElement* root = doc.FirstChildElement("tileset");
        if(root)
        {
            tinyxml2::XMLElement* imageElement = root->FirstChildElement("image");
            if(imageElement)
            {
                std::string source = imageElement->Attribute("source");
                if(!source.empty())
                    imagePath = source;
            }
        }
    }

    return imagePath;
}

World::World(sf::RenderWindow& window, FontHolder& fonts)
    : mTarget(window)
    , mFonts(fonts)
    , mTextures()
    , mPlayer(nullptr)
{
    loadTextures();
    buildScene();
}

void World::update(sf::Time dt)
{
    world.Step(1 / 60.f, 8, 3);

    //mPlayerTank->setVelocity(0.f, 0.f);

    //destroyEntitiesOutsideView();

    while(!mCommandQueue.isEmpty())
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);

    mSceneGraph.removeWrecks();
    //spawnEnemies();


    //for(b2Body* it = world.GetBodyList(); it != 0; it = it->GetNext())
    //{
    //    b2Vec2 pos = it->GetPosition();
    //    float angle = it->GetAngle();

    //    if(it->GetUserData() == "box")
    //    {
    //        sBox.setPosition(pos.x * SCALE, pos.y * SCALE);
    //        sBox.setRotation(angle * DEG);
    //        window.draw(sBox);
    //    }

    //}

    sf::Vector2f pos(mPlayer->getBodyObject()->GetPosition().x, mPlayer->getBodyObject()->GetPosition().y) ;
    mPlayer->setPosition(pos.x * boxScale, pos.y * boxScale);

    mSceneGraph.update(dt, mCommandQueue);

    //handleCollisions();
    //adaptPlayerPosition();
}

void World::draw()
{
    mTarget.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue()
{
    return mCommandQueue;
}

bool World::LoadFromFile(std::string filename)
{
    tinyxml2::XMLDocument levelFile;

    if(levelFile.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS)
    {
        std::cerr << "Loading XML file \"" << filename << "\" failed." << std::endl;
        return false;
    }

    tinyxml2::XMLElement* map;
    map = levelFile.FirstChildElement("map");

    map->QueryIntAttribute("width", &width);
    map->QueryIntAttribute("height", &height);
    map->QueryIntAttribute("tilewidth", &tileWidth);
    map->QueryIntAttribute("tileheight", &tileHeight);

    tinyxml2::XMLElement* tilesetElement;
    tilesetElement = map->FirstChildElement("tileset");

    tilesetElement->QueryIntAttribute("firstgid", &firstTileID);
    std::string fileImagePath = tilesetElement->Attribute("source");

    std::string imagePath = getImagePath(fileImagePath);

    mTextures.load(Textures::Tileset, imagePath);
    mTextures.get(Textures::Tileset).setSmooth(false);

    int columns = mTextures.get(Textures::Tileset).getSize().x / tileWidth;
    int rows = mTextures.get(Textures::Tileset).getSize().y / tileHeight;

    std::vector<sf::IntRect> subRects;

    for(int y = 0; y < rows; y++)
        for(int x = 0; x < columns; x++)
        {
            sf::IntRect rect;

            rect.top = y * tileHeight;
            rect.height = tileHeight;
            rect.left = x * tileWidth;
            rect.width = tileWidth;

            subRects.push_back(rect);
        }

    tinyxml2::XMLElement* layerElement;
    layerElement = map->FirstChildElement("layer");
    while(layerElement)
    {

        tinyxml2::XMLElement* layerDataElement;
        layerDataElement = layerElement->FirstChildElement("data");

        if(layerDataElement == NULL)
        {
            std::cout << "Bad map. No layer information found." << std::endl;
        }

        tinyxml2::XMLElement* tileElement;
        tileElement = layerDataElement->FirstChildElement("tile");

        if(tileElement == NULL)
        {
            std::cout << "Bad map. No tile information found." << std::endl;
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
                finishSprite->setScale(gameScale, gameScale);
                finishSprite->setPosition(x * tileWidth * gameScale, y * tileHeight * gameScale);
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
                    width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].width;
                    height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].height;
                }
                if(objectName == "block") 
                {
                    sf::IntRect objectRect;
                    objectRect.top = y * gameScale;
                    objectRect.left = x * gameScale;
                    objectRect.height = height * gameScale;
                    objectRect.width = width * gameScale;

                    sf::Vector2i tileSize(tileWidth * gameScale, tileHeight * gameScale);

                    std::unique_ptr<Block> block = std::make_unique<Block>(objectRect, tileSize);
                    mSceneLayers[Air]->attachChild(std::move(block));
                }

                if(objectName == "player")
                {
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
                    sf::IntRect rect;
                    rect.top = y * gameScale;
                    rect.left = x * gameScale;
                    rect.height = height * gameScale;
                    rect.width = width * gameScale;

                    std::unique_ptr<Player> player = std::make_unique<Player>(Player::FriedlyPlayer, mTextures, rect);
                    mPlayer = player.get();
                    mPlayer->setTextureRect(subRects[subRectToUse]);
                    mSceneLayers[Air]->attachChild(std::move(player));
                }

                /*Object object;
                object.name = objectName;
                object.type = objectType;
                object.sprite = sprite;*/

                /*
                object.rect = objectRect;*/

               /* tinyxml2::XMLElement* properties;
                properties = objectElement->FirstChildElement("properties");
                if(properties != NULL)
                {
                    tinyxml2::XMLElement* prop;
                    prop = properties->FirstChildElement("property");
                    if(prop != NULL)
                    {
                        while(prop)
                        {
                            std::string propertyName = prop->Attribute("name");
                            std::string propertyValue = prop->Attribute("value");

                            object.properties[propertyName] = propertyValue;

                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }

                objects.push_back(object);*/

                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    }
    else
    {
        std::cout << "No object layers found..." << std::endl;
    }

    return true;
}

//Object World::GetObject(std::string name)
//{
//    for(int i = 0; i < objects.size(); i++)
//        if(objects[i].name == name)
//            return objects[i];
//}
//
//std::vector<Object> World::GetObjects(std::string name)
//{
//    std::vector<Object> vec;
//    for(int i = 0; i < objects.size(); i++)
//        if(objects[i].name == name)
//            vec.push_back(objects[i]);
//
//    return vec;
//}
//
//sf::Vector2i World::GetTileSize()
//{
//    return sf::Vector2i(tileWidth, tileHeight);
//}

void World::loadTextures()
{
   // mTextures.load(Textures::Player, "Media/Textures/player.png");

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

    LoadFromFile("Test.tmx");

    //std::unique_ptr<Player> player = std::make_unique<Player>(Player::FriedlyPlayer, mTextures, mFonts);
    //mPlayer = player.get();
    ////mPlayer->setWall(32, 32, 32, 32);
    //mSceneLayers[Air]->attachChild(std::move(player));

}

