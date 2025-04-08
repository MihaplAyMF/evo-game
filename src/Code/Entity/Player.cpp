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
    , mVelocity(0.f, 0.f)
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

sf::Vector2f getHalfExtents(b2Body* body)
{
    sf::Vector2f max(-FLT_MAX, -FLT_MAX);
    sf::Vector2f min(FLT_MAX, FLT_MAX);

    for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext())
    {
        if (f->GetType() == b2Shape::e_polygon)
        {
            b2PolygonShape* shape = (b2PolygonShape*)f->GetShape();
            for (int i = 0; i < shape->m_count; ++i)
            {
                b2Vec2 worldVertex = body->GetWorldPoint(shape->m_vertices[i]);
                max.x = std::max(max.x, worldVertex.x);
                max.y = std::max(max.y, worldVertex.y);
                min.x = std::min(min.x, worldVertex.x);
                min.y = std::min(min.y, worldVertex.y);
            }
        }
    }

    return sf::Vector2f(
        (max.x - min.x) / 2.f,
        (max.y - min.y) / 2.f
    );
}

void Player::movePlayer(Action type)
{

	b2Vec2 velocity(0.f, 0.f); 

    float playerSpeed = 15.f;
    float gravity = 0.5f;

	switch(type)
	{
	case MoveLeft:
		velocity.x = -playerSpeed; 
		break;
	case MoveRight:
		velocity.x = playerSpeed;
		break;
	case MoveUp:
		velocity.y = -playerSpeed*2;
		break;
	case MoveOnLadder:
		velocity.y = -playerSpeed*2;
		break;
	case NotMove:
		velocity.x = 0.f;
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

        b2Body* otherBody = contact->GetFixtureA()->GetBody();
        if (otherBody == mBody)
            otherBody = contact->GetFixtureB()->GetBody();

	    b2Vec2 otherPos = otherBody->GetPosition();
        velocity.y += gravity;
        if(mIsLadder && type == MoveOnLadder)
        {
            mBody->SetLinearVelocity(b2Vec2(0, velocity.y));
        }
        if(type == MoveUp)
        {	
            if(static_cast<int>(mBody->GetLinearVelocity().y) == 0)
                mIsJumping = true;

            if(contactNormal.y == -1 && velocity.y && mIsJumping)
            {
                mIsJumping = false;
                b2Vec2 newVelocity = mBody->GetLinearVelocity();
                newVelocity.y = -20; 
                mBody->SetLinearVelocity(newVelocity);
            }
        }
        
        contactEdge = contactEdge->next;
    }

    if(type == MoveRight || type == MoveLeft || type == NotMove)
        mBody->SetLinearVelocity(b2Vec2(velocity.x, mBody->GetLinearVelocity().y));

    b2Vec2 currentVelocity = mBody->GetLinearVelocity();
    currentVelocity.y += gravity;  
    mBody->SetLinearVelocity(currentVelocity);
}

unsigned int Player::getCategory() const
{
	return Category::Player;
}

sf::FloatRect Player::getBoundingRect() const
{
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
    mBody->SetAwake(true);
	mBody->SetTransform(b2Vec2(pos.x / boxScale, pos.y / boxScale), mBody->GetAngle());
}
