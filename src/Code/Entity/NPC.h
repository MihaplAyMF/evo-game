#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/String.hpp>

#include "Entity.h"
#include "ResourceIdentifiers.h"

class NPC : public Entity
{
public:
    NPC(const sf::String& name, const TextureHolder& textures, sf::FloatRect rect, sf::IntRect textureRect);

	virtual sf::FloatRect getBoundingRect() const;
	virtual unsigned int getCategory() const;

private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
    
    sf::String mName;
    sf::FloatRect mRect;
    sf::Sprite  mSprite;
};
