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
    float playerSpeed = 7.f;
    float gravity = 0.5f;

    // Рух по горизонталі — обнуляємо x, залишаємо y
    mVelocity = sf::Vector2f(0.f, mVelocity.y);

    switch (type)
    {
    case MoveLeft:
        mVelocity.x = -playerSpeed;
        break;
    case MoveRight:
        mVelocity.x = playerSpeed;
        break;
    case MoveUp:
    case MoveOnLadder:
        mVelocity.y = -playerSpeed * 2;
        break;
    case NotMove:
        mVelocity.x = 0.f;
        break;
    default:
        break;
    }

    mVelocity.y += gravity;

    // Отримуємо розміри гравця
    sf::Vector2f playerHalf = getHalfExtents(mBody);

    b2Vec2 myPos = mBody->GetPosition();
    b2Vec2 correctedPos = myPos;

    // Перебір контактів
    for (b2ContactEdge* contactEdge = mBody->GetContactList(); contactEdge; contactEdge = contactEdge->next)
    {
        b2Contact* contact = contactEdge->contact;
        if (!contact->IsTouching())
            continue;

        b2Body* otherBody = contact->GetFixtureA()->GetBody();
        if (otherBody == mBody)
            otherBody = contact->GetFixtureB()->GetBody();

        b2Vec2 otherPos = otherBody->GetPosition();
        sf::Vector2f otherHalf = getHalfExtents(otherBody);

        b2WorldManifold worldManifold;
        contact->GetWorldManifold(&worldManifold);
        b2Vec2 normal = worldManifold.normal;

        // Обробка колізії по Y (зверху і знизу)
        if (normal.y == -1 && mVelocity.y > 0) {
            correctedPos.y = otherPos.y - otherHalf.y - playerHalf.y;
            mVelocity.y = 0;
        }
        else if (normal.y == 1 && mVelocity.y < 0) {
            correctedPos.y = otherPos.y + otherHalf.y + playerHalf.y;
            mVelocity.y = 0;
        }

        // Обробка колізії по X (зліва і справа)
        if (normal.x == -1 && mVelocity.x > 0) {
            correctedPos.x = otherPos.x - otherHalf.x - playerHalf.x;
            mVelocity.x = 0;
        }
        else if (normal.x == 1 && mVelocity.x < 0) {
            correctedPos.x = otherPos.x + otherHalf.x + playerHalf.x;
            mVelocity.x = 0;
        }
    }

    // Змінюємо позицію фізичного тіла
    correctedPos.x += mVelocity.x / 30.f;
    correctedPos.y += mVelocity.y / 30.f;

    mBody->SetTransform(correctedPos, mBody->GetAngle());

    // Синхронізація SFML спрайта з тілом
    setPosition({ correctedPos.x * 30.f, correctedPos.y * 30.f });

    std::cout << "Box2D pos: " << correctedPos.x * 30.f << ", " << correctedPos.y * 30.f << std::endl;
    std::cout << "Player pos: " << getPosition().x << ", " << getPosition().y << std::endl;
}
/*
void Player::movePlayer(Action type)
{
    mVelocity = sf::Vector2f(0.f, mVelocity.y); 
	float playerSpeed = 7.f;
    float gravity = 0.5f;

    sf::Vector2f pos = getPosition();

	switch(type)
	{
	case MoveLeft:
		mVelocity.x = -playerSpeed; 
		break;
	case MoveRight:
		mVelocity.x = playerSpeed;
		break;
	case MoveUp:
		mVelocity.y = -playerSpeed*2;
		break;
	case MoveOnLadder:
		mVelocity.y = -playerSpeed*2;
		break;
	case NotMove:
		mVelocity.x = 0.f;
		break;
    default:
        break;
    }
    mVelocity.y += gravity;
    
    b2ContactEdge* contactEdge = mBody->GetContactList();
    while(contactEdge)
    {
        b2Contact* contact = contactEdge->contact;
    
        b2Body* otherBody = contact->GetFixtureA()->GetBody();
        if (otherBody == mBody)
            otherBody = contact->GetFixtureB()->GetBody();

	    b2Vec2 otherPos = otherBody->GetPosition();

        b2WorldManifold worldManifold;
        contact->GetWorldManifold(&worldManifold);
        std::cout << "Дотикаємось до об'єкта на координатах: " 
              << otherPos.x * 30 << ", " << otherPos.y * 30 << std::endl;

        b2Vec2 contactNormal = worldManifold.normal;

        if (contactNormal.y == 1 && mVelocity.y < 0)              
            mVelocity.y = 0;
        if (contactNormal.y == -1 && mVelocity.y > 0)             
            mVelocity.y = 0;
        if (contactNormal.x == 1 && mVelocity.x < 0)  
            mVelocity.x = 0;
        if (contactNormal.x == -1 && mVelocity.x > 0) 
            mVelocity.x = 0;

        contactEdge = contactEdge->next;
    }

    std::cout << "Box2d pos: " << mBody->GetPosition().x * 30 << ", " << mBody->GetPosition().y * 30 << std::endl;
    std::cout << "Player pos: " << getPosition().x << ", " << getPosition().y << std::endl; 

    setPosition({pos.x + mVelocity.x, pos.y + mVelocity.y});
}*/

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
