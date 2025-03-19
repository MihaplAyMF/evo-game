#pragma once
#include "ResourceHolder.hpp"

namespace sf
{
	class Texture;
	class Font;
}

enum class Textures
{
	TitleScreen,
	Tileset,
	Player,
	Buttons
};

enum class Fonts
{
	Main,
};

typedef ResourceHolder<sf::Texture, Textures>   TextureHolder;
typedef ResourceHolder<sf::Font, Fonts>			FontHolder;


