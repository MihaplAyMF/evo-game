#pragma once

#include <vector>
#include <functional>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <box2d/box2d.h>

#include "ResourceIdentifiers.h"

class Player;

struct PlayerData
{
	int					   hitpoints;
	float				   speed;
	Textures			   texture;	
	sf::IntRect			   textureRect; 
	//bool				   isDynamic;
};

std::vector<PlayerData>   initializePlayerData();
