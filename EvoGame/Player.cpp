#include <cmath>
#include <string>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "Player.h"
#include "DataTables.h"
#include "Utility.hpp"
#include "CommandQueue.h"
#include "ResourceHolder.hpp"

#include <iostream>

extern const float boxScale;
extern const float gameScale;
extern b2World world;

namespace
{
	const std::vector<PlayerData> Table = initializePlayerData();
}

// constructor method
Player::Player(Type type, const TextureHolder& textures, sf::IntRect rect)
	: Entity(Table[type].hitpoints)
	, mType(type)
	, mSprite(textures.get(Table[type].texture), Table[type].textureRect)
	, isJumping(false)
{
	sf::FloatRect bounds = mSprite.getLocalBounds();
	
	mSprite.setScale(gameScale, gameScale);
	
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(rect.left / boxScale, (rect.top - rect.height) / boxScale);
	bodyDef.fixedRotation = true;
	mBody = world.CreateBody(&bodyDef);
	b2PolygonShape shape;
	shape.SetAsBox((rect.width - 4) / 2 / boxScale, (rect.height - 4) / 2 / boxScale);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f; fixtureDef.friction = 0.0f;
	mBody->CreateFixture(&fixtureDef);
}

// draw method
void Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

void Player::updateCurrent(sf::Time dt, CommandQueue& commands)
{

}

b2Body* Player::getBodyObject()
{
	return mBody;
}

void Player::setTextureRect(sf::IntRect rect)
{
	mSprite.setTextureRect(rect);
}

void Player::movePlayer(b2Vec2 velocity)
{

	b2ContactEdge* contactEdge = mBody->GetContactList();
	while (contactEdge) {
		
		b2Contact* contact = contactEdge->contact;

		b2WorldManifold worldManifold;
		contact->GetWorldManifold(&worldManifold);

		b2Vec2 contactNormal = worldManifold.normal;
		

		if(contactNormal.y == -1 && velocity.y != 0 && isJumping)
		{
			isJumping = false;
			mBody->ApplyLinearImpulse(b2Vec2(0, -6), mBody->GetWorldCenter(), true);
		} 
		else if(static_cast<int>(mBody->GetLinearVelocity().y) == 0)
		{
			isJumping = true;
		}		
    
		// Переход до наступного контакту
		contactEdge = contactEdge->next;
	}
	mBody->SetLinearVelocity(b2Vec2(velocity.x, mBody->GetLinearVelocity().y));
}

unsigned int Player::getCategory() const
{
	return Category::Player;
}

sf::FloatRect Player::getBoundingRect() const
{
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}
