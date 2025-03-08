#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

class Settings {
public:
    static Settings& getInstance() {
        static Settings instance;
        return instance;
    }

    void loadFromFile(const std::string& filename); 
    void saveToFile(const std::string& filename);
    
    int getWidth() const;
    int getHeight() const;     
    bool isFullscreen() const;

    void setWidth(int w);
    void setHeight(int h);
    void setFullscreen(bool f);

private:
    Settings() { loadFromFile("settings.json"); }  
    ~Settings() { saveToFile("settings.json"); }   

    int width = 960;
    int height = 452;
    bool fullscreen = false;
};
