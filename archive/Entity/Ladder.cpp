#include "Ladder.h"

Ladder::Ladder(sf::FloatRect rect)
    : Entity(1)
    , rect(rect)
{ }

sf::FloatRect Ladder::getBoundingRect() const
{
    return getWorldTransform().transformRect(rect);
}

unsigned int Ladder::getCategory() const
{
    return Category::Ladder;
}
