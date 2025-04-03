#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "Settings.h"
#include "Player.h"
#include "DataTables.h"
#include "Utility.hpp"
#include "CommandQueue.h"

#include <iostream>
#include <iterator>

extern const float boxScale;
extern b2World world;

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
	float gameScale = Settings::getInstance().getScale();

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
    sf::Vector2f velocity(0.f, 0.f); 
	float playerSpeed = 10.f;
    float gravity = 0.5f;

    sf::Vector2f pos = getPosition();

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
    default:
        break;
    }
    velocity.y += gravity;
    
    b2ContactEdge* contactEdge = mBody->GetContactList();
    while(contactEdge)
    {

        b2Contact* contact = contactEdge->contact;

        b2WorldManifold worldManifold;
        contact->GetWorldManifold(&worldManifold);

        b2Vec2 contactNormal = worldManifold.normal;

        if (contactNormal.y == 1 && velocity.y < 0)              
            velocity.y = 0;
        if (contactNormal.y == -1 && velocity.y > 0)             
            velocity.y = 0;
        if (contactNormal.x == 1 && velocity.x < 0)  
            velocity.x = 0;
        if (contactNormal.x == -1 && velocity.x > 0) 
            velocity.x = 0;

        contactEdge = contactEdge->next;
    }

    setPosition({pos.x + velocity.x, pos.y + velocity.y});
}

unsigned int Player::getCategory() const
{
	return Category::Player;
}

sf::FloatRect Player::getBoundingRect() const
{
    //return sf::FloatRect();
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

bool Player::isDestroyed() const
{
	return false;
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
