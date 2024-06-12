#pragma once

#include <list>

#include <SFML/Graphics.hpp>

#include "SceneNode.h"


class SpriteNode : public SceneNode
{
public:
	explicit	 SpriteNode(const sf::Texture& texture);
				 SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);
	
	void		 setTextureRect(sf::IntRect rect);

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Sprite	 mSprite;

};