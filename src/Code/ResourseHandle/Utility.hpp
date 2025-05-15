#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp> 

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

float toDegree(float radian);
float toRadian(float degree);

void centerOrigin(sf::Text& text);
void setScale(sf::Sprite& sprite, sf::IntRect rectangle);

int randomInt(int exclusiveMax);

float length(sf::Vector2f vector);
sf::Vector2f unitVector(sf::Vector2f vector);

std::wstring utf8_to_wstring(const std::string& str);

#include "Utility.inl"
