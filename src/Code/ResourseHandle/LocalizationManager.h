#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <list>

class LocalizationManager
{
public:
    LocalizationManager();

    void                    loadLanguage(const std::string& lang);
    std::list<std::string>  loadAvailableLanguages();

    sf::String              getText(const std::string& msgid) const;
    std::vector<sf::String> getDialogues(const std::string& name) const;

private:

    nlohmann::json mTranslations;
};
