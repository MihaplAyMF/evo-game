#include "Settings.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <fstream>
#include <iostream>

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

    mLang = mLocalizationManager.loadAvailableLanguages(); 
    loadFromFile("settings.json"); 
    mLocalizationManager.loadLanguage(*mCurrentLang);
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
            std::string loadedLang(j["video"]["lang"]);
            mFullscreen = j["video"]["fullscreen"];
            mVerSync = j["video"]["verticalSync"];
            mShowFPS = j["video"]["showFPS"];

            auto resIt = std::find(mResolutions.begin(), mResolutions.end(), loadedResolution);
            if (resIt != mResolutions.end()) 
            {
                mCurrentResolution = resIt;
                mNextResolution = mCurrentResolution;
            }

            auto langIt = std::find(mLang.begin(), mLang.end(), loadedLang);
            if (langIt != mLang.end())
            {
                mCurrentLang = langIt;
                mNextLang = mCurrentLang;
            }
        } 
        catch (const std::exception& e) 
        {
            std::cerr << "Bad load data from file" << std::endl;
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
    j["video"]["verticalSync"] = mVerSync; 
    j["video"]["showFPS"] = mShowFPS;
    j["video"]["lang"] = *mCurrentLang;

    std::ofstream file(filename);
    if (file.is_open()) 
    {
        file << j.dump(4); 
    } 
    else 
    {
        std::cerr << "bad save json file" << std::endl;
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

    std::string defaultLang = "en";
    auto langIt = std::find(mLang.begin(), mLang.end(), defaultLang);
    if (langIt != mLang.end())
    {
        mCurrentLang = langIt;
        mNextLang = langIt;
    }

    j["video"]["width"] = res.x;   
    j["video"]["height"] = res.y;   
    j["video"]["fullscreen"] = false;
    j["video"]["verticalSync"] = false; 
    j["video"]["showFPS"] = false;
    j["video"]["lang"] = "en";

    mFullscreen = false;
    mVerSync = false;
    mShowFPS = false;

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

bool Settings::isShowFPS() const
{
    return mShowFPS;
}

bool Settings::isVerSync() const
{
    return mVerSync;
}

bool Settings::isResolutionEqual() const {
    return mCurrentResolution == mNextResolution;
}

void Settings::setFullscreen(bool f) 
{
    mFullscreen = f; 
}

void Settings::setVerSync(bool f)
{
    mVerSync = f;
}

void Settings::setShowFPS(bool f)
{
    mShowFPS = f;
}

void Settings::setFullScreenResolution()
{
    if (!mResolutions.empty())
    {
        mCurrentResolution = mResolutions.begin(); 
        mNextResolution = mCurrentResolution;
    }
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

void Settings::setNextLanguage(Settings::Direction direction) {
    if (mLang.empty()) return;
    switch (direction) {
        case Direction::Next: {
            ++mNextLang;
            if (mNextLang == mLang.end()) {
                mNextLang = mLang.begin();
            }
            break;
        }
        case Direction::Prev: {
            if (mNextLang == mLang.begin()) {
                mNextLang = std::prev(mLang.end());
            } else {
                --mNextLang;
            }
            break;
        }
    }
}
 
void Settings::setCurrentLanguage() 
{
    if (mNextLang != mLang.end()) 
    {
        mCurrentLang = mNextLang;
    }
    std::cout << *mCurrentLang << std::endl;
    mLocalizationManager.loadLanguage(*mCurrentLang);
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

std::string Settings::getNextLang()
{
    return *mNextLang;
}

std::string Settings::getCurrentLang()
{
    return *mCurrentLang;
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

sf::String Settings::getText(const sf::String& msgid) const 
{
    return mLocalizationManager.getText(msgid);
}
std::vector<sf::String> Settings::getDialogues(const std::string& name) const
{
    std::cout << "Nothing" << std::endl;
    return mLocalizationManager.getDialogues(name);
}


float Settings::getScale()
{
    return mScale;
}

float Settings::getAdaptiveValue(int baseValue)
{
    const float baseWidth  = 1920.f;
    const float baseHeight = 1080.f;

    const sf::Vector2u& current = *mCurrentResolution;
    float currentArea = static_cast<float>(current.x * current.y);
    float baseArea = baseWidth * baseHeight;

    float scaleFactor = std::sqrt(currentArea / baseArea);

    scaleFactor = std::clamp(scaleFactor, 0.3f, 1.5f);

    return baseValue * scaleFactor;
}

