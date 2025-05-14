#include "LocalizationManager.h"
#include <SFML/System/String.hpp>
#include <cstdlib>
#include <list>
#include <iostream>
#include <codecvt>
#include <locale>

std::wstring utf8_to_wstring(const std::string& str)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(str);
}

LocalizationManager::LocalizationManager()
{ }

void LocalizationManager::loadLanguage(const std::string& lang)
{
    translations.clear();

    tinyxml2::XMLDocument doc;
    std::string filePath = "Media/Lang/" + lang + ".xml";
    if (doc.LoadFile(filePath.c_str()) != tinyxml2::XML_SUCCESS) 
        abort();

    tinyxml2::XMLElement* root = doc.FirstChildElement("localization");
    if (!root)
        abort(); 

    for (tinyxml2::XMLElement* trans = root->FirstChildElement("translation"); trans; trans = trans->NextSiblingElement()) 
    {
        const char* msgidRaw = trans->FirstChildElement("msgid") ? trans->FirstChildElement("msgid")->GetText() : nullptr;
        const char* msgstrRaw = trans->FirstChildElement("msgstr") ? trans->FirstChildElement("msgstr")->GetText() : nullptr;

        std::wstring msgidW = msgidRaw ? utf8_to_wstring(msgidRaw) : L"";
        std::wstring msgstrW = msgstrRaw ? utf8_to_wstring(msgstrRaw) : msgidW;

        sf::String msgid = msgidW;
        sf::String msgstr = msgstrW;
        
        translations[msgid] = msgstr;
    }
}

std::list<std::string> LocalizationManager::loadAvailableLanguages()
{
    std::list<std::string> availableLanguages;

    tinyxml2::XMLDocument doc;
    if (doc.LoadFile("Media/Lang/languages.xml") != tinyxml2::XML_SUCCESS) 
    {
        std::cerr << "File languages.xml not found" << std::endl;
        abort(); 
    }
    tinyxml2::XMLElement* root = doc.FirstChildElement("languages");
    if (!root)
    { 
        std::cerr << "In file languages.xml not found languages attribute" << std::endl;
        abort();
    }

    for (tinyxml2::XMLElement* lang = root->FirstChildElement("language"); lang; lang = lang->NextSiblingElement())
    {
        const char* code = lang->Attribute("code");
        if (code) {
            availableLanguages.emplace_back(code);
        }
    }

    return availableLanguages;
}

sf::String LocalizationManager::getText(const sf::String& msgid) const 
{
    auto it = translations.find(msgid);
    return it != translations.end() ? it->second : msgid;
}

