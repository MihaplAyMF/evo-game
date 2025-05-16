#include "LocalizationManager.h"

#include <SFML/System/String.hpp>
#include <cstdlib>
#include <list>
#include <iostream>
#include <fstream>
#include <string>

#include "Utility.hpp" 

LocalizationManager::LocalizationManager()
{ }

void LocalizationManager::loadLanguage(const std::string& lang)
{
    std::string filePath = "Media/Lang/" + lang + ".json";
    std::ifstream file(filePath);
    if (!file)
    {
        std::cerr << "Failed to open localization file: " << filePath << std::endl;
        std::abort();
    }

    file >> mTranslations;
}

std::list<std::string> LocalizationManager::loadAvailableLanguages()
{
    std::list<std::string> availableLanguages;

    std::ifstream file("Media/Lang/languages.json");
    if (!file)
    {
        std::cerr << "languages.json not found" << std::endl;
        std::abort();
    }

    nlohmann::json json;
    file >> json;

    if (!json.is_array())
    {
        std::cerr << "languages.json is not a valid array" << std::endl;
        std::abort();
    }

    for (const auto& langCode : json)
    {
        if (langCode.is_string())
            availableLanguages.emplace_back(langCode.get<std::string>());
    }

    return availableLanguages;
}


std::vector<sf::String> LocalizationManager::getDialogues(const std::string& name) const
{
    std::vector<sf::String> result;

    auto it = mTranslations.find(name);
    if (it == mTranslations.end())
        return result;

    const auto& value = *it;

    if (value.is_string())
    {
        std::string str = value.get<std::string>();
        result.emplace_back(utf8_to_wstring(str));
    }
    else if (value.is_array())
    {
        for (const auto& item : value)
        {
            if (item.is_string())
            {
                std::string str = item.get<std::string>();
                result.emplace_back(utf8_to_wstring(str));
            }
        }
    }

    return result;
}


sf::String LocalizationManager::getText(const std::string& msgid) const 
{
    auto it = mTranslations.find(msgid);
    if (it != mTranslations.end() && it->is_string())
        return sf::String(utf8_to_wstring(it->get<std::string>()));
    else
        return msgid; 
}
