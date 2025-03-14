#include "Utility.hpp"

#include <cmath>
#include <ctime>
#include <cassert>
#include <random>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

namespace
{
	std::default_random_engine createRandomEngine()
	{
		auto seed = static_cast<unsigned long>(std::time(nullptr));
		return std::default_random_engine(seed);
	}

	auto RandomEngine = createRandomEngine();
}

std::string toString(sf::Keyboard::Scan key)
{
    #define BOOK_KEYTOSTRING_CASE(KEY) case sf::Keyboard::Scan::KEY: return #KEY;

	switch(key)
	{
		BOOK_KEYTOSTRING_CASE(Unknown)
			BOOK_KEYTOSTRING_CASE(A)
			BOOK_KEYTOSTRING_CASE(B)
			BOOK_KEYTOSTRING_CASE(C)
			BOOK_KEYTOSTRING_CASE(D)
			BOOK_KEYTOSTRING_CASE(E)
			BOOK_KEYTOSTRING_CASE(F)
			BOOK_KEYTOSTRING_CASE(G)
			BOOK_KEYTOSTRING_CASE(H)
			BOOK_KEYTOSTRING_CASE(I)
			BOOK_KEYTOSTRING_CASE(J)
			BOOK_KEYTOSTRING_CASE(K)
			BOOK_KEYTOSTRING_CASE(L)
			BOOK_KEYTOSTRING_CASE(M)
			BOOK_KEYTOSTRING_CASE(N)
			BOOK_KEYTOSTRING_CASE(O)
			BOOK_KEYTOSTRING_CASE(P)
			BOOK_KEYTOSTRING_CASE(Q)
			BOOK_KEYTOSTRING_CASE(R)
			BOOK_KEYTOSTRING_CASE(S)
			BOOK_KEYTOSTRING_CASE(T)
			BOOK_KEYTOSTRING_CASE(U)
			BOOK_KEYTOSTRING_CASE(V)
			BOOK_KEYTOSTRING_CASE(W)
			BOOK_KEYTOSTRING_CASE(X)
			BOOK_KEYTOSTRING_CASE(Y)
			BOOK_KEYTOSTRING_CASE(Z)
			BOOK_KEYTOSTRING_CASE(Num0)
			BOOK_KEYTOSTRING_CASE(Num1)
			BOOK_KEYTOSTRING_CASE(Num2)
			BOOK_KEYTOSTRING_CASE(Num3)
			BOOK_KEYTOSTRING_CASE(Num4)
			BOOK_KEYTOSTRING_CASE(Num5)
			BOOK_KEYTOSTRING_CASE(Num6)
			BOOK_KEYTOSTRING_CASE(Num7)
			BOOK_KEYTOSTRING_CASE(Num8)
			BOOK_KEYTOSTRING_CASE(Num9)
			BOOK_KEYTOSTRING_CASE(Escape)
			BOOK_KEYTOSTRING_CASE(LControl)
			BOOK_KEYTOSTRING_CASE(LShift)
			BOOK_KEYTOSTRING_CASE(LAlt)
			BOOK_KEYTOSTRING_CASE(LSystem)
			BOOK_KEYTOSTRING_CASE(RControl)
			BOOK_KEYTOSTRING_CASE(RShift)
			BOOK_KEYTOSTRING_CASE(RAlt)
			BOOK_KEYTOSTRING_CASE(RSystem)
			BOOK_KEYTOSTRING_CASE(Menu)
			BOOK_KEYTOSTRING_CASE(LBracket)
			BOOK_KEYTOSTRING_CASE(RBracket)
			BOOK_KEYTOSTRING_CASE(Semicolon)
			BOOK_KEYTOSTRING_CASE(Comma)
			BOOK_KEYTOSTRING_CASE(Period)
			BOOK_KEYTOSTRING_CASE(Apostrophe)
			BOOK_KEYTOSTRING_CASE(Slash)
			BOOK_KEYTOSTRING_CASE(Backslash)
			BOOK_KEYTOSTRING_CASE(Grave)
			BOOK_KEYTOSTRING_CASE(Equal)
			BOOK_KEYTOSTRING_CASE(Hyphen)
			BOOK_KEYTOSTRING_CASE(Space)
			BOOK_KEYTOSTRING_CASE(Enter)
			BOOK_KEYTOSTRING_CASE(Backspace)
			BOOK_KEYTOSTRING_CASE(Tab)
			BOOK_KEYTOSTRING_CASE(PageUp)
			BOOK_KEYTOSTRING_CASE(PageDown)
			BOOK_KEYTOSTRING_CASE(End)
			BOOK_KEYTOSTRING_CASE(Home)
			BOOK_KEYTOSTRING_CASE(Insert)
			BOOK_KEYTOSTRING_CASE(Delete)
			BOOK_KEYTOSTRING_CASE(Left)
			BOOK_KEYTOSTRING_CASE(Right)
			BOOK_KEYTOSTRING_CASE(Up)
			BOOK_KEYTOSTRING_CASE(Down)
			BOOK_KEYTOSTRING_CASE(Numpad0)
			BOOK_KEYTOSTRING_CASE(Numpad1)
			BOOK_KEYTOSTRING_CASE(Numpad2)
			BOOK_KEYTOSTRING_CASE(Numpad3)
			BOOK_KEYTOSTRING_CASE(Numpad4)
			BOOK_KEYTOSTRING_CASE(Numpad5)
			BOOK_KEYTOSTRING_CASE(Numpad6)
			BOOK_KEYTOSTRING_CASE(Numpad7)
			BOOK_KEYTOSTRING_CASE(Numpad8)
			BOOK_KEYTOSTRING_CASE(Numpad9)
			BOOK_KEYTOSTRING_CASE(F1)
			BOOK_KEYTOSTRING_CASE(F2)
			BOOK_KEYTOSTRING_CASE(F3)
			BOOK_KEYTOSTRING_CASE(F4)
			BOOK_KEYTOSTRING_CASE(F5)
			BOOK_KEYTOSTRING_CASE(F6)
			BOOK_KEYTOSTRING_CASE(F7)
			BOOK_KEYTOSTRING_CASE(F8)
			BOOK_KEYTOSTRING_CASE(F9)
			BOOK_KEYTOSTRING_CASE(F10)
			BOOK_KEYTOSTRING_CASE(F11)
			BOOK_KEYTOSTRING_CASE(F12)
			BOOK_KEYTOSTRING_CASE(F13)
			BOOK_KEYTOSTRING_CASE(F14)
			BOOK_KEYTOSTRING_CASE(F15)
			BOOK_KEYTOSTRING_CASE(Pause)
	}

	return "";
}

void centerOrigin(sf::Sprite& sprite)
{
    sf::FloatRect bounds = sprite.getGlobalBounds();
    sprite.setOrigin(bounds.position + bounds.size / 2.f);
}

void centerOrigin(sf::Text& text)
{
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.position + bounds.size / 2.f);
}

float toDegree(float radian)
{
	return 180.f / 3.141592653589793238462643383f * radian;
}

float toRadian(float degree)
{
	return 3.141592653589793238462643383f / 180.f * degree;
}

void setScale(sf::Sprite& sprite, sf::IntRect rectangle)
{
    sf::FloatRect localBounds = sprite.getLocalBounds();

    float scaleX = rectangle.size.x / localBounds.size.x;
    float scaleY = rectangle.size.y / localBounds.size.y;
    
    sprite.setScale({scaleX, scaleY});
}

int randomInt(int exclusiveMax)
{
	std::uniform_int_distribution<> distr(0, exclusiveMax - 1);
	return distr(RandomEngine);
}

float length(sf::Vector2f vector)
{
	return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

sf::Vector2f unitVector(sf::Vector2f vector)
{
	assert(vector != sf::Vector2f(0.f, 0.f));
	return vector / length(vector);
}
