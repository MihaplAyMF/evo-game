#include "Settings.h"

#include <SFML/Window/VideoMode.hpp>
#include <iostream>

Settings::Settings() 
{
    mResolutions.push_back(sf::Vector2u(800, 600));
    mResolutions.push_back(sf::Vector2u(1024, 768));
    mResolutions.push_back(sf::Vector2u(1280, 720));
    mResolutions.push_back(sf::Vector2u(1366, 768));
    mResolutions.push_back(sf::Vector2u(1600, 900));
    mResolutions.push_back(sf::Vector2u(1920, 1080));
    mResolutions.push_back(sf::Vector2u(2560, 1440));
    mResolutions.push_back(sf::Vector2u(3840, 2160));    

    loadFromFile("settings.json");    
}

Settings::~Settings() 
{ 
    saveToFile("settings.json"); 
}   

void Settings::loadFromFile(const std::string& filename) 
{
    std::ifstream file(filename);
    if (file.is_open()) {
        try 
        {
            nlohmann::json j;
            file >> j;

            mWidth = j["video"]["width"];
            mHeight = j["video"]["height"];
            mFullscreen = j["video"]["fullscreen"];
        } 
        catch (const std::exception& e) 
        {
            std::abort();
        }
    }
    else 
    {
        saveDefaultSettingsToFile(filename);
    }
}

void Settings::saveToFile(const std::string& filename) 
{
    nlohmann::json j;
    j["video"]["width"] = mWidth;
    j["video"]["height"] = mHeight;
    j["video"]["fullscreen"] = mFullscreen;

    std::ofstream file(filename);
    if (file.is_open()) 
    {
        file << j.dump(4); 
    } 
    else 
    {
        std::abort();
    }
}

void Settings::saveDefaultSettingsToFile(const std::string& filename) 
{
    nlohmann::json j;

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    std::cout << desktop.size.x << ", " << desktop.size.y << std::endl;

    auto it = std::find(mResolutions.begin(), mResolutions.end(), sf::Vector2u(desktop.size.x, desktop.size.y));
    if (it != mResolutions.end())
    {
        mCurrentResolution = it;
    } 
    else
    {
        mCurrentResolution = mResolutions.begin();
        mCurrentResolution = std::find(mResolutions.begin(), mResolutions.end(), getClosestResolution(desktop.size.x, desktop.size.y));
    }

    const auto& res = *mCurrentResolution;

    j["video"]["width"] = res.x;   
    j["video"]["height"] = res.y;   
    j["video"]["fullscreen"] = false; 

    mWidth = res.x;
    mHeight = res.y;
    mFullscreen = false;

    std::ofstream file(filename);
    if (file.is_open()) 
    {
        file << j.dump(4); 
    } 
    else 
    {
        std::abort(); 
    }
}

int Settings::getWidth() const 
{ 
    return mWidth; 
}

int Settings::getHeight() const 
{ 
    return mHeight; 
}

bool Settings::isFullscreen() const 
{
    return mFullscreen; 
}

sf::Vector2u Settings::getResolution() const
{
    return *mCurrentResolution;
}

sf::Vector2u Settings::getClosestResolution(unsigned int width, unsigned int height) const
{
    sf::Vector2u closest = mResolutions.front();   
    unsigned int minDifference = std::abs((int)(width - closest.x)) + std::abs((int)(height - closest.y));

    for (const auto& res : mResolutions) 
    {
        unsigned int diff = std::abs((int)(width - res.x)) + std::abs((int)(height - res.y));
        if (diff < minDifference) 
        {
            closest = res;
            minDifference = diff;
        }
    }
    return closest;
}

void Settings::setWidth(int w)
{ 
    mWidth = w; 
}

void Settings::setHeight(int h) 
{
    mHeight = h; 
}

void Settings::setFullscreen(bool f) 
{
    mFullscreen = f; 
}

