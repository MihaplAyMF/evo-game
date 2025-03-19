#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Entity.h"

class Block : public Entity
{
public:
	Block(sf::FloatRect objectRect, sf::Vector2i tileSize);

	b2Body* getBodyObject();

private:
	b2Body* mBody;

};
