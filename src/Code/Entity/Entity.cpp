#include <cassert>

#include "Entity.h"

Entity::Entity(int hitpoints)
	: mHitpoints(hitpoints)
{ }


void Entity::repair(int points)
{
	assert(points > 0);

	mHitpoints += points;
}

void Entity::damage(int points)
{
	assert(points > 0);

	mHitpoints -= points;
}

void Entity::destroy()
{
	mHitpoints = 0;
}

void Entity::remove()
{
	destroy();
}

int Entity::getHitpoints() const
{
	return mHitpoints;
}

void Entity::setHitpoints(int HP) 
{
    mHitpoints = HP;
}

bool Entity::isDestroyed() const
{
	return mHitpoints <= 0;
}

bool Entity::isMoving() const 
{
    return false;    
}

void Entity::updateCurrent(sf::Time dt, CommandQueue& commands)
{ }
