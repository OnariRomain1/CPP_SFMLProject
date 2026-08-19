cmake_minimum_required(VERSION 3.28)

project(C-Projects LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
)

FetchContent_MakeAvailable(SFML)

add_executable(C-Projects
    src/game.cpp
)

target_link_libraries(
    C-Projects
    PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)