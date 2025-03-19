
cmake_minimum_required(VERSION 3.10)

project(EvoGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS "Projecct name: ${PROJECT_NAME}")

set (SRC_DIR "${CMAKE_SOURCE_DIR}/src/Code")

file(GLOB_RECURSE SOURCES
    ${SRC_DIR}/*.cpp
)

add_executable(EvoGame ${SOURCES})

set(VCPKG_FILE_DIR ${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-linux)
set(SFML_DIR "${VCPKG_FILE_DIR}/share/sfml")
set(nlohmann_json_DIR "${VCPKG_FILE_DIR}/share/nlohmann_json")
set(box2d_DIR "${VCPKG_FILE_DIR}/share/box2d")
set(tinyxml2_DIR "${VCPKG_FILE_DIR}/share/tinyxml2")

find_package(SFML COMPONENTS Network Graphics Window Audio System CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)
find_package(tinyxml2 CONFIG REQUIRED)

target_link_libraries(EvoGame
    SFML::Network SFML::Graphics SFML::Window SFML::Audio SFML::System
    nlohmann_json::nlohmann_json
    box2d::box2d
    tinyxml2::tinyxml2
)

target_include_directories(EvoGame PRIVATE 
    ${SRC_DIR}
    ${SRC_DIR}/State
    ${SRC_DIR}/State/StateLogic
    ${SRC_DIR}/ResourseHandle
    ${SRC_DIR}/Component
    ${SRC_DIR}/Entity
    ${SRC_DIR}/GameLogic
    ${SRC_DIR}/InputHandle   
    ${SRC_DIR}/Node
)
