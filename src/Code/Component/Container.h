#pragma once

#include <memory>
#include <vector>

#include <SFML/System/Time.hpp>

#include "Component.h"

namespace GUI
{
	class Container : public Component
	{
	public:
		typedef std::shared_ptr<Container> Ptr;
		
		Container();

		void pack(Component::Ptr component);
		
		virtual bool isSelectable() const;
		virtual void handleEvent(const sf::Event& event);
		virtual void update(sf::Time dt);

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		
		bool hasSelection() const;
		void select(size_t index);
		void selectNext();
		void selectPrevious();

		std::vector<Component::Ptr> mChildren;
		int						    mSelectedChild;
	};
};
