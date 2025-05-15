#include "Ladder.h"

Ladder::Ladder(sf::FloatRect rect)
    : Entity(1)
    , mRect(rect)
{ }

sf::FloatRect Ladder::getBoundingRect() const
{
    return getWorldTransform().transformRect(mRect);
}

unsigned int Ladder::getCategory() const
{
    return Category::Ladder;
}
