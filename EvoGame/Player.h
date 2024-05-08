#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Entity.h"
#include "CommandQueue.h"
#include "ResourceIdentifiers.h"


class Player : public Entity
{
public:

	enum Type
	{
		FriedlyPlayer, 
		TypeCount
	};

	explicit Player(Type type, const TextureHolder& textures, sf::IntRect rect);

	b2Body* getBodyObject();
	void setTextureRect(sf::IntRect rect);

	void movePlayer(b2Vec2 velocity);

	virtual unsigned int  getCategory() const;
	//virtual sf::FloatRect getBoundingRect() const;
	//virtual void		  remove();
	//virtual bool		  isMarkedForRemoval() const;
	//bool				  isAllied() const;
	//float				  getMaxSpeed() const;

	//void				  increaseFireRate();
	//void				  increaseSpread();
	//void				  collectMissile(unsigned int count);

	//void				  fire();
	//void				  launchMissile();

private:
	virtual void		  drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void		  updateCurrent(sf::Time dt, CommandQueue& commands);

	//void				  updateMovementPattern(sf::Time dt);
	//void				  checkProjectileLaunch(sf::Time dt, CommandQueue& commands);
	//void				  checkPickupDrop(CommandQueue& commands);

	//void				  createBullets(SceneNode& node, const TextureHolder& texture) const;
	//void				  createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float y0ffset, const TextureHolder& textures) const;
	//void				  createPickup(SceneNode& node, const TextureHolder& textures) const;

	//void				  updateTexts();
	//void				  updateRollAnimation();

	b2Body* mBody;
	Type	   mType;
	sf::Sprite mSprite;

	bool isJumping;
	/*Animation  mExplosion;
	sf::Time   mFireCountdown;
	sf::Time   mMissileCountdown;
	Command    mFireCommand;
	Command	   mMissileCommand;
	Command    mDropPickupCommand;*/

	/*TextNode* mHealthDisplay;
	TextNode* mMissileDisplay;*/

	/*bool	   mIsFiring;
	bool	   mIsLaunchingMissile;
	bool	   mSpawnedPickup;
	bool       mShowExplosion;*/

	/*int		   mMissileAmmo;
	int		   mSpreadLevel;
	int		   mFireRateLevel;
	int		   mDirectionIndex;*/

	//float	   mTravelledDistance;

};
