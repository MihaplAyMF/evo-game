#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Entity.h"

class Coin : public Entity
{
public:
	Coin(const TextureHolder& textures, int objectID, sf::FloatRect rect);

	b2Body* getBodyObject();	
	
	virtual unsigned int getCategory() const;
	virtual sf::FloatRect getBoundingRect() const;

	int getObjectID();
private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	
	b2Body*    mBody;
	sf::Sprite mSprite;
	int		   mObjectID;
};