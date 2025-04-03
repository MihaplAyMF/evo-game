#include <box2d/b2_world.h>

#include "DataTables.h"
#include "Player.h"

b2Vec2 gravity(0.f, 15.f);
b2World world(gravity);
float boxScale = 30.f;

std::vector<PlayerData> initializePlayerData()
{
    std::vector<PlayerData> data(Player::TypeCount);

    data[Player::FriedlyPlayer].hitpoints = 3;
    data[Player::FriedlyPlayer].speed = 200.f;
    data[Player::FriedlyPlayer].texture = Textures::Tileset;
    data[Player::FriedlyPlayer].textureRect = sf::IntRect({80, 144}, {16, 16});

    return data;
}   

float getBoxScale()
{
    return boxScale;
}
b2World& getWorld()
{
    return world;
}
