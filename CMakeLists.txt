
cmake_minimum_required(VERSION 3.10)

project(EvoGame)

set(CMAKE_CXX_STANDARD 17)

message(STATUS "Projecct name: ${PROJECT_NAME}")

set (SRC_DIR "${CMAKE_SOURCE_DIR}/src/Code")

file(GLOB_RECURSE SOURCES
    ${SRC_DIR}/*.cpp
)

add_executable(EvoGame ${SOURCES})

set(VCPKG_FILE_DIR ${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-linux)
set(SFML_DIR "${VCPKG_FILE_DIR}/share/sfml")
set(nlohmann_json_DIR "${VCPKG_FILE_DIR}/share/nlohmann_json")

find_package(SFML COMPONENTS Network Graphics Window Audio System CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

target_link_libraries(EvoGame
    SFML::Network SFML::Graphics SFML::Window SFML::Audio SFML::System
    nlohmann_json::nlohmann_json
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
