#pragma once

#include <memory>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/NonCopyable.hpp>

namespace GUI
{
    class Component : public sf::Drawable, public sf::NonCopyable, public sf::Transformable
	{
	public:
		typedef std::shared_ptr<Component> Ptr;

					 Component();
		virtual		 ~Component();
        virtual bool isSelectable() const = 0;

		bool		 isSelected() const;
		virtual void select();
		virtual void deselect();
		virtual bool isActive() const;
		virtual void activate();
		virtual void deactivate();
		virtual void handleEvent(const sf::Event& event) = 0;
		virtual void update(sf::Time dt) = 0;

	private:
		bool mIsSelected;
		bool mIsActive;
	};
}
