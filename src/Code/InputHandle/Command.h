#pragma once

#include <functional>
#include <cassert>

#include <SFML/System/Time.hpp>

class SceneNode;

struct Command
{
	Command();

	std::function<void(SceneNode&, sf::Time)> action;
	unsigned int							  category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
{
	return [=](SceneNode& node, sf::Time dt)
	{
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		fn(static_cast<GameObject&>(node), dt);
	};
}
