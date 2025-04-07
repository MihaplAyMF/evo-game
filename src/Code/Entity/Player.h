#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Entity.h"
#include "CommandQueue.h"
#include "ResourceIdentifiers.h"
#include "DataTables.h"

class Player : public Entity
{
public:

	enum Type
	{
		FriedlyPlayer, 
		TypeCount
	};

	explicit Player(Type type, const TextureHolder& textures, sf::FloatRect rect);

	b2Body* getBodyObject();
	void setTextureRect(sf::IntRect rect);

	void movePlayer(Action type);

	virtual unsigned int  getCategory() const;
	virtual sf::FloatRect getBoundingRect() const;
	virtual bool isDestroyed() const;
    bool getIsExit() const;

	void setIsLadder(bool isLadder);
	void setIsExit(bool isExit);
	void setPos(sf::Vector2f pos);

private:
	virtual void		  drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void		  updateCurrent(sf::Time dt, CommandQueue& commands);

	b2Body*		mBody;
	Type	    mType;
	sf::Sprite  mSprite;

	bool mIsJumping;
	bool mIsLadder;
	bool mIsExit;

    sf::Vector2f mVelocity;

	sf::Time   mFireCountdown;
	sf::Time   mMissileCountdown;
	Command    mFireCommand;
	Command	   mMissileCommand;
	Command    mDropPickupCommand;

};
