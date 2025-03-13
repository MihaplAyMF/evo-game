#include "Block.h"

extern const float boxScale;
extern b2World world;

Block::Block(sf::FloatRect rect, sf::Vector2i tileSize)
	: Entity(1)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set((rect.left + tileSize.x / 2 * (rect.width / tileSize.x - 1)) / boxScale,
						 (rect.top + tileSize.y / 2 * (rect.height / tileSize.y - 1)) / boxScale);
	mBody = world.CreateBody(&bodyDef);
	b2PolygonShape shape;
	shape.SetAsBox(rect.width / 2 / boxScale, rect.height / 2 / boxScale);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 0.0f; fixtureDef.friction = 0.1f;
	mBody->CreateFixture(&fixtureDef);
}

b2Body* Block::getBodyObject()
{
	return mBody;
}
