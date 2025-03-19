[![en](https://img.shields.io/badge/Language-English-red.svg)](https://github.com/MihaplAyMF/evo-game/blob/main/README.md)
[![ua](https://img.shields.io/badge/Language-Ukrainian-green.svg)](https://github.com/MihaplAyMF/evo-game/blob/main/README.ua.md)

# EvoGame

## Встановлення та збірка

### Необхідні інструменти

1. Перед початком встановіть наступні інструменти:
2. Git
3. CMake


### Клонування проєкту
    
 ```git clone https://github.com/MihaplAyMF/evo-game.git```
 ```cd evo-game```

### Встановлення Vcpkg

 ```mkdir vcpkg && cd vcpkg
 git clone https://github.com/microsoft/vcpkg.git
 ./bootstrap-vcpkg.sh  # Для Linux/macOS
 .\bootstrap-vcpkg.bat  # Для Windows```

### Встановлення необхідних бібліотек

 ```./vcpkg install sfml box2d tinyxml2 nlohmann-json  # Linux/macOS
 .\vcpkg.exe install sfml box2d tinyxml2 nlohmann-json  # Windows```

### Збірка проєкту

 ```cd ..
 mkdir build && cd build
 cmake .. -G "Ninja"  # Для Windows рекомендується Ninja
 make  # Linux/macOS
 ninja  # Windows```

### Запуск гри

``` ./my_new_pet_project  # Linux/macOS
 .\my_new_pet_project.exe  # Windows```

### Замітки
* Усі бібліотеки встановлюються у внутрішню папку проєкту, що спрощує компіляцію.
* Для Windows рекомендується використовувати Ninja або Visual Studio.
* Для Linux/macOS потрібно мати make, gcc, g++.
* Для Windows бажано використовувати MSVC або MinGW.


