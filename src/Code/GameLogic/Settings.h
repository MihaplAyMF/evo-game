#pragma once

#include <SFML/System/Vector2.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include <list>

class Settings
{
public:
    static Settings& getInstance()
    {
        static Settings instance;
        return instance;
    }

    void loadFromFile(const std::string& filename); 
    void saveToFile(const std::string& filename);
    void saveDefaultSettingsToFile(const std::string& filename);
        
    int getWidth() const;
    int getHeight() const;    
    bool isFullscreen() const;
    sf::Vector2u getResolution() const;
    sf::Vector2u getClosestResolution(unsigned int width, unsigned int height) const;

    void setWidth(int w);
    void setHeight(int h);
    void setFullscreen(bool f);
    void setResolution(sf::Vector2u r);


private:
    Settings(); 
    ~Settings();

    int mWidth;
    int mHeight;
    bool mFullscreen;
    
    std::list<sf::Vector2u> mResolutions;
    std::list<sf::Vector2u>::iterator mCurrentResolution;
};
