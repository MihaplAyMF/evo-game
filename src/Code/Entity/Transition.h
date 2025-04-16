#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

#include "Entity.h"

class Transition : public Entity
{
public:   
    Transition(sf::FloatRect rect, std::string mapName, bool isEntry);

	virtual sf::FloatRect getBoundingRect() const;
	virtual unsigned int getCategory() const;
    
    void setMapName(std::string mapName);
    void setPosition();

    std::string getMapName();
    sf::Vector2f getPosition();
    bool getIsEntry();

private:
	sf::FloatRect mRect;
    sf::Vector2f mStartPos;
    std::string mMapName;
    bool mIsEntry;
};
