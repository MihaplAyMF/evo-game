#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "Coin.h"
#include "ResourceHolder.hpp"

extern const float boxScale;
extern const float gameScale;
extern b2World world;

Coin::Coin(const TextureHolder& textures, sf::IntRect rect, sf::Vector2i tileSize)
	: Entity(1)
	, mSprite(textures.get(Textures::Tileset), sf::IntRect(80, 112, 16, 16))
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

	//fixtureDef.shape = &shape;
	//fixtureDef.density = 0.0f; fixtureDef.friction = 0.1f;
	//mBody->CreateFixture(&fixtureDef);
}	

b2Body* Coin::getBodyObject()
{
	return mBody;
}
unsigned int Coin::getCategory() const
{
	return Category::Coin;
}

void Coin::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}