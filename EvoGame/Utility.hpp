#pragma once

#include <sstream>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp> 

//#include "Animation.h"

namespace sf 
{
	class Sprite;
	class Text;
}

template <typename T>
std::string toString(const T& other);

std::string toString(sf::Keyboard::Key key);

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);
//void centerOrigin(Animation& animation);

float toDegree(float radian);
float toRadian(float degree);

int randomInt(int exclusiveMax);

float length(sf::Vector2f vector);
sf::Vector2f unitVector(sf::Vector2f vector);

#include "Utility.inl"
