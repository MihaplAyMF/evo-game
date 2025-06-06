#include <algorithm>
#include <cassert>
#include <cmath>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "SceneNode.h"
#include "Command.h"
#include "Utility.hpp"

SceneNode::SceneNode(Category::Type category)
	: mChildren()
	, mParent(nullptr)
	, mDefaultCategory(category)
	, mIsBackground(false)
{ }

void SceneNode::attachChild(Ptr child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(),
		[&](Ptr& p) -> bool { return p.get() == &node; });
	
	assert(found != mChildren.end());
	
	Ptr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);

	return result;
}

bool SceneNode::hasChild(const SceneNode* node) const 
{
    for (const auto& child : mChildren) 
    {
        if (child.get() == node) 
        {
            return true;
        }
    }
    return false;
}

void SceneNode::cleanup()
{
    mChildren.erase(
    std::remove_if(mChildren.begin(), mChildren.end(),
        [](const Ptr& child)
        {
            return !child->isProtected();
        }),
        mChildren.end()
    );
}

void SceneNode::update(sf::Time dt, CommandQueue& commands)
{
	updateCurrent(dt, commands);
	updateChildren(dt, commands);
}

void SceneNode::updateCurrent(sf::Time dt, CommandQueue& commands)
{

}

void SceneNode::updateChildren(sf::Time dt, CommandQueue& commands)
{
	for(Ptr& child : mChildren)
	{
		child->update(dt, commands);
	}
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	drawCurrent(target, states);
	drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(const Ptr& child : mChildren)
		child->draw(target, states);
}

void SceneNode::drawBoundingRect(sf::RenderTarget& target, sf::RenderStates stetes) const
{
	sf::FloatRect rect = getBoundingRect();

	sf::RectangleShape shape;
	shape.setPosition(sf::Vector2f({rect.position.x, rect.position.y}));
	shape.setSize(sf::Vector2f({rect.size.x, rect.size.y}));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1.f);	

	target.draw(shape);	

}

void SceneNode::removeWrecks()
{
	auto wreckfieldBegin = std::remove_if(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));
	mChildren.erase(wreckfieldBegin, mChildren.end());

	std::for_each(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::removeWrecks));
}

bool SceneNode::isProtected() const 
{ 
    return false; 
}

bool SceneNode::isDestroyed() const
{
	return false;
}
bool SceneNode::isMoving() const 
{
    return false;    
}
bool SceneNode::isBackground() const
{
	return mIsBackground;
}

void SceneNode::setBackground(int flag)
{
	mIsBackground = flag;
}

bool SceneNode::isMarkedForRemoval() const
{
	return isDestroyed();
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for(const SceneNode* node = this; node != nullptr; node = node->mParent)
	{
		transform = node->getTransform() * transform;
	}
	return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

void SceneNode::onCommand(const Command& command, sf::Time dt)
{
	if(command.category & getCategory())
		command.action(*this, dt);
		
	for(Ptr& child : mChildren)
		child->onCommand(command, dt);
}

unsigned int SceneNode::getCategory() const
{
	return mDefaultCategory;
}

void SceneNode::checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs)
{
	checkNodeCollision(sceneGraph, collisionPairs);

	for(Ptr& child : sceneGraph.mChildren)	
		checkSceneCollision(*child, collisionPairs);
}

void SceneNode::checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs)
{
    bool state1 = isMoving();
    bool state2 = node.isMoving();

    if(this == &node || isDestroyed() || node.isDestroyed()
        || isBackground() || node.isBackground()
        || !(isMoving() || node.isMoving()))
		return;

	if(collision(*this, node))
		collisionPairs.insert(std::minmax(this, &node));

	for(Ptr& child : mChildren)
		child->checkNodeCollision(node, collisionPairs);
}

sf::FloatRect SceneNode::getBoundingRect() const
{
	return sf::FloatRect();
}

bool collision(const SceneNode& lhs, const SceneNode& rhs)
{
    auto intersection = lhs.getBoundingRect().findIntersection(rhs.getBoundingRect());
    return intersection.has_value(); 
}

float distance(const SceneNode& lhs, const SceneNode& rhs)
{
	return length(lhs.getWorldPosition() - rhs.getWorldPosition());
}
