#include "Exit.h"

Exit::Exit(sf::FloatRect rect)
    : Entity(1)
    , rect(rect)
{}

sf::FloatRect Exit::getBoundingRect() const
{
    return getWorldTransform().transformRect(rect);
}

unsigned int Exit::getCategory() const
{
    return Category::Exit;
}
