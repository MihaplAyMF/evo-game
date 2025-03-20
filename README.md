[![en](https://img.shields.io/badge/Language-English-red.svg)](https://github.com/MihaplAyMF/evo-game/blob/master/README.md)
[![ua](https://img.shields.io/badge/Language-Ukrainian-green.svg)](https://github.com/MihaplAyMF/evo-game/blob/master/README.ua.md)

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
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh  # For Linux/macOS
.\bootstrap-vcpkg.bat  # For Windows
```

### Installing Required Libraries

```sh
./vcpkg install sfml box2d tinyxml2 nlohmann-json  # Linux/macOS
.\vcpkg.exe install sfml box2d tinyxml2 nlohmann-json  # Windows
```

### Building the Project

```sh
./vcpkg install sfml box2d tinyxml2 nlohmann-json  # Linux/macOS
.\vcpkg.exe install sfml box2d tinyxml2 nlohmann-json  # Windows
```

### Running the Project

```sh
cd ..
mkdir build && cd build
cmake ..
make  # Linux/macOS
```
On Windows, if using Visual Studio, after generating CMake files in the build directory, open the .sln file and build the project from there.
