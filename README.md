[![en](https://img.shields.io/badge/Language-English-red.svg)](https://github.com/MihaplAyMF/evo-game/blob/main/README.md)
[![ua](https://img.shields.io/badge/Language-Ukrainian-green.svg)](https://github.com/MihaplAyMF/evo-game/blob/main/README.ua.md)

# EvoGame

## Installation and Build

### Required Tools

1. Before starting, install the following tools:
2. Git
3. CMake

### Cloning the Project

~~~sh
git clone https://github.com/MihaplAyMF/evo-game.git
cd evo-game
~~~

### Installing Vcpkg

```sh
mkdir vcpkg && cd vcpkg
git clone https://github.com/microsoft/vcpkg.git
./bootstrap-vcpkg.sh  # For Linux/macOS
.\bootstrap-vcpkg.bat  # For Windows
```

### Installing Required Libraries

```sh
mkdir vcpkg && cd vcpkg
git clone https://github.com/microsoft/vcpkg.git
./bootstrap-vcpkg.sh  # For Linux/macOS
.\bootstrap-vcpkg.bat  # For Windows
```

### Building the Project

```sh
./vcpkg install sfml box2d tinyxml2 nlohmann-json  # Linux/macOS
.\vcpkg.exe install sfml box2d tinyxml2 nlohmann-json  # Windows
```

### Running the Project

```sh
./my_new_pet_project  # Linux/macOS
.\my_new_pet_project.exe  # Windows
```

### Notes
* All libraries are installed inside the project directory to simplify compilation.
* For Windows, it is recommended to use Ninja or Visual Studio.
* For Linux/macOS, make sure to have make, gcc, and g++ installed.
* For Windows, it is preferable to use MSVC or MinGW.
