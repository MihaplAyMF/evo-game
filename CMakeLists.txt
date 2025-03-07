
cmake_minimum_required(VERSION 3.10)

project(MyProject)

set(CMAKE_CXX_STANDARD 17)

message(STATUS "Projecct name: ${PROJECT_NAME}")

set (SRC_DIR "${CMAKE_SOURCE_DIR}/src/Code")

file(GLOB_RECURSE SOURCES
    ${SRC_DIR}/*.cpp
)

add_executable(MyProject ${SOURCES})

set(VCPKG_FILE_DIR ${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-linux)
set(SFML_DIR "${VCPKG_FILE_DIR}/share/sfml")

find_package(SFML COMPONENTS Network Graphics Window Audio System CONFIG REQUIRED)

target_link_libraries(MyProject
    SFML::Network SFML::Graphics SFML::Window SFML::Audio SFML::System
)

target_include_directories(MyProject PRIVATE 
    ${SRC_DIR}
    ${SRC_DIR}/State
    ${SRC_DIR}/ResourseHandle
    ${SRC_DIR}/Component
    ${SRC_DIR}/Entity
)
