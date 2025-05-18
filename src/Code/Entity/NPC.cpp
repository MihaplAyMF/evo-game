#include "NPC.h"
#include "Settings.h"
#include "Category.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

NPC::NPC(const sf::String& name, const TextureHolder& textures, sf::FloatRect rect, sf::IntRect textureRect)
    : Entity(1)
    , mName(name)
    , mRect(rect)
    , mSprite(textures.get(Textures::Tileset), textureRect)
{
    float gameScale = Settings::getInstance().getScale();

    mSprite.setScale({gameScale, gameScale});
    mSprite.setPosition({rect.position.x, rect.position.y - rect.size.y});
    
    mDialogues = Settings::getInstance().getDialogues(name);
}

sf::FloatRect NPC::getBoundingRect() const
{
    return getWorldTransform().transformRect(mRect);
}

unsigned int NPC::getCategory() const
{
    return Category::NPC;
}

const std::vector<sf::String>& NPC::getDialogues() const
{
    return mDialogues;
}

void NPC::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

void NPC::updateCurrent(sf::Time dt, CommandQueue& commands)
{}
