#include <box2d/box2d.h>

#include "DataTables.h"
#include "player.h"

extern const float boxScale = 30.f;
extern const float deg = 57.29577f;
extern const float gameScale = 2.0f;

b2Vec2 gravity(0.f, 9.8f);
b2World world(gravity);

std::vector<PlayerData> initializePlayerData()
{
    std::vector<PlayerData> data(Player::TypeCount);

    data[Player::FriedlyPlayer].hitpoints = 100;
    data[Player::FriedlyPlayer].speed = 200.f;
    data[Player::FriedlyPlayer].texture = Textures::Tileset;
    data[Player::FriedlyPlayer].textureRect = sf::IntRect(0, 0, 16, 16);
    //data[Player::FriedlyPlayer].isDynamic = true;ì

    return data;
}   
