#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Entity.h"

class Exit : public Entity
{
public:
	Exit(sf::FloatRect rect);
	virtual sf::FloatRect getBoundingRect() const;

	virtual unsigned int getCategory() const;

private:
	sf::FloatRect rect;

};