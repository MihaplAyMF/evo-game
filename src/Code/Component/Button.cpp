#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Button.h"
#include "Utility.hpp"
#include "Settings.h"

float gameScale = Settings::getInstance().getScale();

namespace GUI
{
	Button::Button(const FontHolder& fonts, const TextureHolder& textures)
		: mCallback()
		, mSprite(textures.get(Textures::Tileset), sf::IntRect({80, 144}, {16, 16}))
		, mText(fonts.get(Fonts::Main), "", 16)
		, mIsActive(false)
	{
		changeTexture(Unselected);
		mSprite.setScale(sf::Vector2f(gameScale, gameScale));
        mText.setPosition({mText.getPosition().x + 45, mText.getPosition().y});
	}

	void Button::setCallback(Callback callback)
	{
		mCallback = std::move(callback);
	}

	void Button::setText(sf::String text)
	{
		mText.setString(text);
		mText.setCharacterSize(30);
		mText.setPosition({mText.getPosition().x, mText.getPosition().y});
	}

	void Button::setToggle(bool flag) 
	{
		mIsActive = flag;
	}

    sf::Text& Button::getText() 
	{
		return mText;
	}
 
    bool Button::isActive()
    {
        return mSprite.getTextureRect() == sf::IntRect({80, 144}, {16, 16});
    }    

    bool Button::isSelectable() const
	{
		return true;
	}

	void Button::select()
	{
		Component::select();

		changeTexture(Selected);
	}

	void Button::deselect()
	{
		Component::deselect();

		changeTexture(Unselected);
	}

	void Button::activate()
	{
		Component::activate();

		if(mIsActive)
			changeTexture(Unselected);

		if(mCallback)
			mCallback();

		if(!mIsActive)
			deactivate();
	}

	void Button::deactivate()
	{
		Component::deactivate();

		if(isSelected())
			changeTexture(Selected);
		else
			changeTexture(Unselected);
	}

	void Button::handleEvent(const sf::Event& event)
	{ }

	void Button::update(sf::Time dt)
	{
	}

	void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(mSprite, states);
		target.draw(mText, states);
	}

	void Button::changeTexture(Type buttonType)
	{
		if(buttonType == Selected)
		{
			sf::IntRect textureRect(sf::Vector2i(80, 144), sf::Vector2i(16, 16));
			mSprite.setTextureRect(textureRect);
		}
		else
		{
			sf::IntRect textureRect(sf::Vector2i(0, 0), sf::Vector2i(0, 0));
			mSprite.setTextureRect(textureRect);
		}
	}
}

	
