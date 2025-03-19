#include <box2d/b2_world.h>
#include <box2d/box2d.h>

#include "DataTables.h"
#include "Player.h"

b2Vec2 gravity(0.f, 9.8f);
b2World world(gravity);
extern const float boxScale = 30.f;// * 2.15f;

std::vector<PlayerData> initializePlayerData()
{
    std::vector<PlayerData> data(Player::TypeCount);

    data[Player::FriedlyPlayer].hitpoints = 3;
    data[Player::FriedlyPlayer].speed = 200.f;
    data[Player::FriedlyPlayer].texture = Textures::Tileset;
    data[Player::FriedlyPlayer].textureRect = sf::IntRect({0, 0}, {16, 16});

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
