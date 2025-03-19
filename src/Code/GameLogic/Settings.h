#pragma once

#include <SFML/System/Vector2.hpp>
#include <nlohmann/json.hpp>
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
    bool isResolutionEqual() const;
    
    void setFullscreen(bool f);
    void setCurrentResolution();
    void setNextResolution(Direction d);
    void setScale(float s);

    sf::Vector2u getCurrentResolution() const;
    sf::Vector2u getNextResolution() const;
    sf::Vector2u getMaxResolution() const;
    sf::Vector2u getClosestResolution(unsigned int width, unsigned int height) const;
    
    float getScale();  
    float getAdaptiveValue(int baseValue);

private:
    Settings(); 
    ~Settings();

    bool  mFullscreen;
    float mScale;

    std::list<sf::Vector2u> mResolutions;
    std::list<sf::Vector2u>::iterator mCurrentResolution;
    std::list<sf::Vector2u>::iterator mNextResolution;
    sf::Vector2u mMaxResolution;
};
