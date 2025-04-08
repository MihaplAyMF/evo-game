#pragma once

#include <box2d/box2d.h>

#include "SceneNode.h"

class Entity : public SceneNode
{
public:
	explicit Entity(int hitpoints);

	int getHitpoints() const;
    void setHitpoints(int HP);

	void repair(int points);
	void damage(int points);
	void destroy();
	
	virtual void remove();
	virtual bool isDestroyed() const;

protected:
	virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

private:
	int mHitpoints;
};
