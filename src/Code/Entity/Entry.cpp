#include "Entry.h"
#include "Category.h"

Entry::Entry(sf::FloatRect rect)
    : Entity(1)
    , rect(rect)
{ }

sf::FloatRect Entry::getBoundingRect() const
{
    return getWorldTransform().transformRect(rect);
}

unsigned int Entry::getCategory() const
{
    return Category::Entry;
}
