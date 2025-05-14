#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>
#include <tinyxml2.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <map>
#include <string>
#include <list>

class LocalizationManager
{
public:
    LocalizationManager();

    void                    loadLanguage(const std::string& lang);
    std::list<std::string>  loadAvailableLanguages();

    sf::String  getText(const sf::String& msgid) const;
    std::string   getCurrentLanguage() const;

private:

    std::map<sf::String, sf::String> translations;
};
