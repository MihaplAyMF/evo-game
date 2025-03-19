#include "Block.h"
#include "DataTables.h"

extern const float boxScale;

Block::Block(sf::FloatRect rect, sf::Vector2i tileSize)
	: Entity(1)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set((rect.position.x + tileSize.x / 2 * (rect.size.x / tileSize.x - 1)) / boxScale,
	                     (rect.position.y + tileSize.y / 2 * (rect.size.y / tileSize.y - 1)) / boxScale);

    b2World& world = getWorld();
    mBody = world.CreateBody(&bodyDef);
	
    b2PolygonShape shape;
	shape.SetAsBox(rect.size.x / 2 / boxScale, rect.size.y / 2 / boxScale);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 0.0f; fixtureDef.friction = 0.1f;
	mBody->CreateFixture(&fixtureDef);
}

b2Body* Block::getBodyObject()
{
	return mBody;
}
