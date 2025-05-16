#pragma once

#include <SFML/System/Vector2.hpp>
#include <nlohmann/json.hpp>
#include <list>

#include "LocalizationManager.h"

#define _(STR) Settings::getInstance().getText(STR)

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
    bool isShowFPS() const;
    bool isVerSync() const;
    bool isResolutionEqual() const;
    
    void setFullscreen(bool f);
    void setVerSync(bool f);
    void setShowFPS(bool f);
    void setFullScreenResolution();
    void setCurrentResolution();
    void setNextResolution(Direction d);

    void setCurrentLanguage();    
    void setNextLanguage(Direction direction); 
    void setScale(float s);

    sf::Vector2u getCurrentResolution() const;
    sf::Vector2u getNextResolution() const;
    sf::Vector2u getMaxResolution() const;
    sf::Vector2u getClosestResolution(unsigned int width, unsigned int height) const;
    std::string getNextLang();
    std::string getCurrentLang();
    sf::String getText(const sf::String& msgid) const;
    std::vector<sf::String> getDialogues(const std::string& name) const;

    float getScale();  
    float getAdaptiveValue(int baseValue);

private:
    Settings(); 
    ~Settings();

    bool        mFullscreen;
    bool        mShowFPS;
    bool        mVerSync;
    float       mScale;

    LocalizationManager mLocalizationManager;
    std::list<std::string> mLang;
    std::list<std::string>::iterator mCurrentLang;
    std::list<std::string>::iterator mNextLang;
    
    std::list<sf::Vector2u> mResolutions;
    std::list<sf::Vector2u>::iterator mCurrentResolution;
    std::list<sf::Vector2u>::iterator mNextResolution;
    sf::Vector2u mMaxResolution;
};
