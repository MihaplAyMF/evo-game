#include "Transition.h"
#include "Category.h"
#include <SFML/System/Vector2.hpp>

Transition::Transition(sf::FloatRect rect, std::string mapName, bool isEntry)
    : Entity(1)
    , mRect(rect)
    , mMapName(mapName)
    , mIsEntry(isEntry)
{ }

sf::FloatRect Transition::getBoundingRect() const
{
    return getWorldTransform().transformRect(mRect);
}

unsigned int Transition::getCategory() const
{
    return Category::Transition;
}

void Transition::setMapName(std::string mapName)
{
    mMapName = mapName;
}

std::string Transition::getMapName()
{
    return mMapName;
}

sf::Vector2f Transition::getPosition()
{
    return {mRect.position.x, mRect.position.y};
}

bool Transition::getIsEntry()
{
    return mIsEntry;
}
