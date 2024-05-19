#pragma once
#include <SFML/Graphics/Sprite.hpp>

#include "Entity.h"

class Coin : public Entity
{
public:
	Coin(const TextureHolder& textures, sf::IntRect rect, sf::Vector2i tileSize);

	b2Body* getBodyObject();	
	
	virtual unsigned int getCategory() const;
private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	
	b2Body*    mBody;
	sf::Sprite mSprite;

};