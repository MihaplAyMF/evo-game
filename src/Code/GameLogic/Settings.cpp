#include "Settings.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <fstream>

Settings::Settings()
{
    mScale = 4.f;

    mMaxResolution = sf::VideoMode::getDesktopMode().size;
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();

    for (const auto& mode : modes) 
    {
        if(mode.bitsPerPixel == 32)
            mResolutions.push_back(mode.size);
    }

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

            sf::Vector2u loadedResolution(j["video"]["width"],  j["video"]["height"]);
            mFullscreen = j["video"]["fullscreen"];
            
            auto it = std::find(mResolutions.begin(), mResolutions.end(), loadedResolution);
            if (it != mResolutions.end()) 
            {
                mCurrentResolution = it;
                mNextResolution = mCurrentResolution;
            }
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
    j["video"]["width"] = mCurrentResolution->x;
    j["video"]["height"] = mCurrentResolution->y;
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

    auto it = std::find(mResolutions.begin(), mResolutions.end(), sf::Vector2u(mMaxResolution.x, mMaxResolution.y));
    if (it != mResolutions.end())
    {
        mCurrentResolution = it;
    } 
    else
    {
        mCurrentResolution = mResolutions.begin();
        mCurrentResolution = std::find(mResolutions.begin(), mResolutions.end(), getClosestResolution(mMaxResolution.x, mMaxResolution.y));
    }

    const auto& res = *mCurrentResolution;
    mNextResolution = mCurrentResolution;

    j["video"]["width"] = res.x;   
    j["video"]["height"] = res.y;   
    j["video"]["fullscreen"] = false; 

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

bool Settings::isFullscreen() const 
{
    return mFullscreen; 
}

bool Settings::isResolutionEqual() const {
    return mCurrentResolution == mNextResolution;
}

void Settings::setFullscreen(bool f) 
{
    mFullscreen = f; 
}

void Settings::setCurrentResolution()
{
    if (mNextResolution != mResolutions.end()) {
        mCurrentResolution = mNextResolution;
    }
}

void Settings::setNextResolution(Direction direction)
{
    if (mResolutions.empty()) return;

    switch (direction) 
    {
        case Direction::Next: 
        {
            ++mNextResolution;
            if (mNextResolution == mResolutions.end()) 
            {
                mNextResolution = mResolutions.begin();   
            }
            break;
        }
        case Direction::Prev:
        {    
            if (mNextResolution == mResolutions.begin()) 
            {
                mNextResolution = std::prev(mResolutions.end());
            } 
            else 
            {
                --mNextResolution;
            }
            break;
        }
    }
}

void Settings::setScale(float s)
{
    mScale = s;
}

sf::Vector2u Settings::getNextResolution() const
{
    return *mNextResolution;
}

sf::Vector2u Settings::getCurrentResolution() const
{
    return *mCurrentResolution;
}

sf::Vector2u Settings::getMaxResolution() const
{
    return mMaxResolution;
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

float Settings::getScale()
{
    return mScale;
}

float Settings::getAdaptiveValue(int baseValue)
{
    return baseValue;
}
