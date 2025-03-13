# Вказуємо мінімальну версію CMake
cmake_minimum_required(VERSION 3.10)

# Назва проєкту
project(EvoGame)

# Вказуємо стандарт C++ (можна змінити, якщо потрібно)
set(CMAKE_CXX_STANDARD 17)

# Діагностичне повідомлення для перевірки
message(STATUS "Project name: ${PROJECT_NAME}")

# Шлях до папки з вихідними файлами
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

# Збираємо всі `.cpp` файли з папки src
file(GLOB_RECURSE SOURCES
    ${SRC_DIR}/Code/*.cpp
)

# Додаємо виконуваний файл для основного проєкту
add_executable(EvoGame ${SOURCES} ${SRC_DIR}/Code/Main.cpp)

# Додаємо директорії для заголовочних файлів SFML, використовуючи target_include_directories
target_include_directories(EvoGame PRIVATE 
    ${SRC_DIR}/Library/SFML/include
    ${SRC_DIR}/Library/Box2d/include
    ${SRC_DIR}/Code
    ${SRC_DIR}/Code/Component
    ${SRC_DIR}/Code/Entity
    ${SRC_DIR}/Code/GameLogic
    ${SRC_DIR}/Code/InputHandle
    ${SRC_DIR}/Code/Node
    ${SRC_DIR}/Code/State
    ${SRC_DIR}/Code/ResourseHandle
    ${SRC_DIR}/Library
    ${SRC_DIR}/Media
)

# Додаємо директорії для статичних бібліотек
link_directories(${CMAKE_SOURCE_DIR}/src/Library/SFML/lib)

# Лінкуємо з необхідними бібліотеками SFML (статичні бібліотеки)
target_link_libraries(EvoGame 
    ${CMAKE_SOURCE_DIR}/src/Library/SFML/lib/libsfml-audio-s.a
    ${CMAKE_SOURCE_DIR}/src/Library/SFML/lib/libsfml-graphics-s.a
    ${CMAKE_SOURCE_DIR}/src/Library/SFML/lib/libsfml-network-s.a
    ${CMAKE_SOURCE_DIR}/src/Library/SFML/lib/libsfml-window-s.a
    ${CMAKE_SOURCE_DIR}/src/Library/SFML/lib/libsfml-system-s.a
    X11 Xrandr Xcursor Xinerama Xi Xxf86vm udev
)

# Визначаємо, що ми використовуємо статичні бібліотеки SFML
target_compile_definitions(EvoGame PRIVATE SFML_STATIC)

# Додаємо директорії для тестування
enable_testing()

