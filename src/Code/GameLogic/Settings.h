#pragma once

#include <SFML/System/Vector2.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include <list>

class Settings
{
public:

    enum class Direction { Next, Prev };

    static Settings& getInstance()
    {
        static Settings instance;
        return instance;
    }

    void loadFromFile(const std::string& filename); 
    void saveToFile(const std::string& filename);
    void saveDefaultSettingsToFile(const std::string& filename);
        
    bool isFullscreen() const;

    void setFullscreen(bool f);
    void setResolution();
    void setNextResolution(Direction d);

    sf::Vector2u getResolution() const;
    sf::Vector2u getNextResolution() const;
    sf::Vector2u getClosestResolution(unsigned int width, unsigned int height) const;
    
    int getAdaptiveValue(int baseValue);

private:
    Settings(); 
    ~Settings();

    bool  mFullscreen;

    std::list<sf::Vector2u> mResolutions;
    std::list<sf::Vector2u>::iterator mCurrentResolution;
    std::list<sf::Vector2u>::iterator mNextResolution;
};
