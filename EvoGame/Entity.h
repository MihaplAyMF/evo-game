#pragma once

#include <box2d/box2d.h>

#include "SceneNode.h"
#include "DataTables.h"

class Entity : public SceneNode
{
public:
	explicit Entity(int hitpoints/*, bool isDynamic = false*/);

	//void		 setVelocity(sf::Vector2f velocity);
	//void		 setVelocity(float vx, float vy);
	//void		 accelerate(sf::Vector2f velocity);
	//void		 accelerate(float vx, float vy);
	//sf::Vector2f getVelocity() const;

	int getHitpoints() const;
	void repair(int points);
	void damage(int points);
	void destroy();
	
	//void setWall(int x, int y, int w, int h);

	virtual void remove();
	virtual bool isDestroyed() const;

protected:
	virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

private:
	int mHitpoints;
	//bool isDynamic;
};