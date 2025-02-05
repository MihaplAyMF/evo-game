#pragma once

#include <vector>
#include <string>
#include <memory>
#include <functional>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Component.h"
#include "ResourceIdentifiers.h"
#include "ResourceHolder.hpp"

namespace GUI
{
	class Button : public Component
	{
	public:
		typedef std::shared_ptr<Button> Ptr;
		typedef std::function<void()> Callback;

		enum Type
		{
			Selected,
			Unselected,
			ButtonCount
		};

		Button(const FontHolder& fonts, const TextureHolder& textures);

		void setCallback(Callback callback);
		void setText(sf::String text);
		void setToggle(bool flag);

		virtual bool isSelectable() const;
		virtual void select();
		virtual void deselect();
		
		virtual void activate();
		virtual void deactivate();

		virtual void handleEvent(const sf::Event& event);
		virtual void update(sf::Time dt);


	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void		 changeTexture(Type buttonType);

		Callback		   mCallback;
		sf::Sprite		   mSprite;
		sf::Text		   mText;
		bool			   mIsToggle; 
	};
}
