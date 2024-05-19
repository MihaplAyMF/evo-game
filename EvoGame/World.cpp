#include <iostream>
#include <tinyxml2.h>

#include "World.h"
#include "Block.h"

extern const float boxScale;
extern const float gameScale;
extern b2World world;

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
    , mWorldView(window.getDefaultView())
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

    while(!mCommandQueue.isEmpty())
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);

    mSceneGraph.removeWrecks();
    
    sf::Vector2f pos(mPlayer->getBodyObject()->GetPosition().x, mPlayer->getBodyObject()->GetPosition().y) ;
    mPlayer->setPosition(pos.x * boxScale, pos.y * boxScale);

    mSceneGraph.update(dt, mCommandQueue);

    handleCollisions();
}

void World::draw()
{
    mTarget.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue()
{
    return mCommandQueue;
}

void World::cleanup()
{
    b2Body* body = world.GetBodyList();
    while(body != nullptr)
    {
        b2Body* nextBody = body->GetNext(); 
        world.DestroyBody(body); 
        body = nextBody;
    }
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

                sf::IntRect rect;
                rect.top = y * gameScale;
                rect.left = x * gameScale;
                rect.height = height * gameScale;
                rect.width = width * gameScale;

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
                    sf::Vector2i tileSize(tileWidth * gameScale, tileHeight * gameScale);

                    std::unique_ptr<Coin> coin = std::make_unique<Coin>(mTextures, rect, tileSize);
                    coinBody.push_back(coin.get());
                    mSceneLayers[Air]->attachChild(std::move(coin));
                }

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

}

void World::handleCollisions()
{
    for(b2ContactEdge* ce = mPlayer->getBodyObject()->GetContactList(); ce; ce = ce->next)
    {
        bool state = false;

        for(int i = 0; i < coinBody.size(); i++)
            if(ce->contact->GetFixtureB()->GetBody() == coinBody[i]->getBodyObject())
            {
                coinBody[i]->getBodyObject()->DestroyFixture(coinBody[i]->getBodyObject()->GetFixtureList());
                coinBody[i]->remove();
                coinBody.erase(coinBody.begin() + i); state = true;
                break;
            }
        if(state == true)
            break;

    }
}

bool World::hasAlivePlayer()
{
    if(!getEvoGameBounds().intersects(mPlayer->getBoundingRect()))
    {
        mPlayer->remove();
        return false;
    }
    return true;

}

sf::FloatRect World::getViewBounds() const
{
    return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}

sf::FloatRect World::getEvoGameBounds() const
{
    sf::FloatRect bounds = getViewBounds();

    bounds.top -= 100.f;
    bounds.height += 200.f;

    return bounds;
}

