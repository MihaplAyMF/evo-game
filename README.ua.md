[![en](https://img.shields.io/badge/Language-English-red.svg)](https://github.com/MihaplAyMF/evo-game/blob/master/README.md)
[![ua](https://img.shields.io/badge/Language-Ukrainian-green.svg)](https://github.com/MihaplAyMF/evo-game/blob/master/README.ua.md)

# EvoGame

## Встановлення та збірка

### Необхідні інструменти

1. Перед початком встановіть наступні інструменти:
2. Git
3. CMake


### Клонування проєкту
    
```sh
git clone https://github.com/MihaplAyMF/evo-game.git
cd evo-game
```

### Встановлення Vcpkg

```sh
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh  # Для Linux/macOS
.\bootstrap-vcpkg.bat  # Для Windows
```

### Встановлення необхідних бібліотек

```sh
./vcpkg install sfml box2d tinyxml2 nlohmann-json  # Linux/macOS
.\vcpkg.exe install sfml box2d tinyxml2 nlohmann-json  # Windows
```

### Збірка проєкту

```sh
cd ..
mkdir build && cd build
cmake ..
make  # Linux/macOS
```

### Запуск гри

```sh
 ./my_new_pet_project  # Linux/macOS
.\my_new_pet_project.exe  # Windows
```
На Windows, якщо використовується Visual Studio, після генерації файлів CMake у build потрібно відкрити .sln файл та зібрати проєкт звідти.

