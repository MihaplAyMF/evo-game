#include "Settings.h"

void Settings::loadFromFile(const std::string& filename) 
{
    std::ifstream file(filename);
    if (file.is_open()) {
        try 
        {
            nlohmann::json j;
            file >> j;

            width = j["video"]["width"];
            height = j["video"]["height"];
            fullscreen = j["video"]["fullscreen"];
        } 
        catch (const std::exception& e) 
        {
            std::cerr << "Error loading settings: " << e.what() << std::endl;
        }
    }
    else 
    {
        std::cerr << "Settings file not found, creating default settings." << std::endl;
        saveToFile(filename);
    }
}

void Settings::saveToFile(const std::string& filename) 
{
    nlohmann::json j;
    j["video"]["width"] = width;
    j["video"]["height"] = height;
    j["video"]["fullscreen"] = fullscreen;

    std::ofstream file(filename);
    if (file.is_open()) 
    {
        file << j.dump(4); 
    } 
    else 
    {
        std::cerr << "Error saving settings to file!" << std::endl;
    }
}

int Settings::getWidth() const { return width; }
int Settings::getHeight() const { return height; }
bool Settings::isFullscreen() const { return fullscreen; }

void Settings::setWidth(int w) { width = w; }
void Settings::setHeight(int h) { height = h; }
void Settings::setFullscreen(bool f) { fullscreen = f; }

