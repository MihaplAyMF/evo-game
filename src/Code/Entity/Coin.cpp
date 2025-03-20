#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "Coin.h"
#include "Settings.h"

Coin::Coin(const TextureHolder& textures, int objectID, sf::FloatRect rect)
	: Entity(1)
	, mSprite(textures.get(Textures::Tileset), sf::IntRect({80, 112}, {16, 16}))
	, mObjectID(objectID)
{

	float gameScale = Settings::getInstance().getScale();
	mSprite.setScale({gameScale, gameScale});
	mSprite.setPosition({rect.position.x, rect.position.y - rect.size.y});
}	

b2Body* Coin::getBodyObject()
{
	return mBody;
}
unsigned int Coin::getCategory() const
{
	return Category::Coin;
}

sf::FloatRect Coin::getBoundingRect() const
{
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

int Coin::getObjectID()
{
	return mObjectID;
}

void Coin::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}
