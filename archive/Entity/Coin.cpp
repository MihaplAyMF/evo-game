#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "Coin.h"
#include "ResourceHolder.hpp"

extern const float boxScale;
extern const float gameScale;
extern b2World world;

Coin::Coin(const TextureHolder& textures, int objectID, sf::FloatRect rect)
	: Entity(1)
	, mSprite(textures.get(Textures::Tileset), sf::IntRect(80, 112, 16, 16))
	, mObjectID(objectID)
{
	mSprite.setScale(gameScale, gameScale);
	mSprite.setPosition(rect.left, rect.top - rect.height);

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(rect.left / boxScale, (rect.top - rect.height) / boxScale);
	bodyDef.fixedRotation = true;

	mBody = world.CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(rect.width / 2 / boxScale, rect.height / 2 / boxScale);

	b2FixtureDef fixtureDef;
	mBody->CreateFixture(&shape, 1.0f);
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