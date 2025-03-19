#pragma once

#include <vector>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <box2d/box2d.h>

#include "ResourceIdentifiers.h"

enum Action
{
	MoveUp,
	MoveLeft,
	MoveRight,
	MoveOnLadder,
	NotMove,
	PressF,
	ActionCount
};

class Player;

struct PlayerData
{
	int					   hitpoints;
	float				   speed;
	Textures			   texture;	
	sf::IntRect			   textureRect; 
};

std::vector<PlayerData>   initializePlayerData();
float getBoxScale();
b2World& getWorld();
