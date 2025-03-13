#pragma once

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <vector>
#include <memory>
#include <set>
#include <utility>

#include "CommandQueue.h"
#include "Category.h"

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;
	typedef std::pair<SceneNode*, SceneNode*> Pair;

	explicit			  SceneNode(Category::Type category = Category::None);

	void				  attachChild(Ptr child);
	Ptr					  detachChild(const SceneNode& node);
	void				  cleanup();

	void				  update(sf::Time dt, CommandQueue& commands);

	void virtual		  onCommand(const Command& command, sf::Time dt);
	virtual unsigned int  getCategory() const;

	void				  checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);
	void				  checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs);
	virtual sf::FloatRect getBoundingRect() const;
	
	virtual bool		  isMarkedForRemoval() const;
	virtual bool		  isDestroyed() const;
	virtual bool          isBackground() const;

	void				  setBackground(int flag);

	void				  removeWrecks();
	sf::Transform		  getWorldTransform() const;
	sf::Vector2f		  getWorldPosition() const;

private:
	virtual void		  updateCurrent(sf::Time dt, CommandQueue& command);
	void			 	  updateChildren(sf::Time dt, CommandQueue& commands);

	virtual void		  draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual	void		  drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void				  drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
	void				  drawBoundingRect(sf::RenderTarget& target, sf::RenderStates stetes) const;

	std::vector<Ptr> mChildren;
	SceneNode*		 mParent;
	Category::Type   mDefaultCategory;

	int mIsBackground;
};

bool  collision(const SceneNode& lhs, const SceneNode& rhs);
float distance(const SceneNode& lhs, const SceneNode& rhs);