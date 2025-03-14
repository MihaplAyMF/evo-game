#include <cmath>
#include <string>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "Settings.h"
#include "Player.h"
#include "DataTables.h"
#include "Utility.hpp"
#include "CommandQueue.h"
#include "ResourceHolder.hpp"

extern const float boxScale;
extern b2World world;

float gameScale = Settings::getInstance().getScale();

namespace
{
	const std::vector<PlayerData> Table = initializePlayerData();
}

Player::Player(Type type, const TextureHolder& textures, sf::FloatRect rect)
	: Entity(Table[type].hitpoints)
	, mType(type)
	, mSprite(textures.get(Table[type].texture), Table[type].textureRect)
	, mIsJumping(false)
	, mIsLadder(false)
	, mIsExit(false)
{
	sf::FloatRect bounds = mSprite.getLocalBounds();
	
	mSprite.setScale({gameScale, gameScale});
	
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(rect.position.x / boxScale, (rect.position.y - rect.size.y) / boxScale);
	bodyDef.fixedRotation = true;
	mBody = world.CreateBody(&bodyDef);
	b2PolygonShape shape;
	shape.SetAsBox((rect.size.x - 7) / 2 / boxScale, (rect.size.y - 4) / 2 / boxScale);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f; fixtureDef.friction = 0.0f;
	mBody->CreateFixture(&fixtureDef);
}

void Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

void Player::updateCurrent(sf::Time dt, CommandQueue& commands)
{}

b2Body* Player::getBodyObject()
{
	return mBody;
}

void Player::setTextureRect(sf::IntRect rect)
{
	mSprite.setTextureRect(rect);
}

void Player::movePlayer(Action type)
{
	b2Vec2 velocity(0.f, 0.f); 
	float playerSpeed = 5.f;

	switch(type)
	{
	case MoveLeft:
		velocity.x = -playerSpeed; 
		break;
	case MoveRight:
		velocity.x = playerSpeed;
		break;
	case MoveUp:
		velocity.y = -playerSpeed;
		break;
	case MoveOnLadder:
		velocity.y = -playerSpeed;
		break;
	case NotMove:
		velocity.x = 0.f;
		velocity.y = 0.f;
		break;
	}

	if(mIsLadder && type == MoveOnLadder)
	{
		mBody->SetLinearVelocity(b2Vec2(0, velocity.y));
	}
	if(type == MoveUp)
	{	
		if(static_cast<int>(mBody->GetLinearVelocity().y) == 0)
			mIsJumping = true;

		b2ContactEdge* contactEdge = mBody->GetContactList();
		while(contactEdge)
		{

			b2Contact* contact = contactEdge->contact;

			b2WorldManifold worldManifold;
			contact->GetWorldManifold(&worldManifold);

			b2Vec2 contactNormal = worldManifold.normal;

			if(contactNormal.y == 1)
				contactNormal.y = -1;

			if(contactNormal.y == -1 && velocity.y && mIsJumping)
			{
				mIsJumping = false;
				mBody->ApplyLinearImpulse(b2Vec2(0, -5.2), mBody->GetWorldCenter(), true);
			}
	
			contactEdge = contactEdge->next;
		}
	}
	if(type == MoveRight || type == MoveLeft || type == NotMove)
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

bool Player::getIsExit() const
{
	return mIsExit;
}

void Player::setIsLadder(bool isLadder)
{
	mIsLadder = isLadder;
}

void Player::setIsExit(bool isExit)
{
	mIsExit = isExit;
}

void Player::setPos(sf::Vector2f pos)
{
	mBody->SetTransform(b2Vec2(pos.x / boxScale, pos.y / boxScale), mBody->GetAngle());
}
