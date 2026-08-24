cmake_minimum_required(VERSION 3.28)

project(CPP_SFMLProject LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# --------------------
# SFML
# --------------------
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
)

FetchContent_MakeAvailable(SFML)

# --------------------
# GLAD
# --------------------
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v2.0.8
    SOURCE_SUBDIR cmake
)

FetchContent_MakeAvailable(glad)

glad_add_library(
    glad_gl_core_33
    STATIC
    REPRODUCIBLE
    API gl:core=3.3
)

# --------------------
# OpenGL
# --------------------
find_package(OpenGL REQUIRED)

# --------------------
# Executable
# --------------------
add_executable(main
   
    src/game.cpp

)
add_executable(primitives
    src/Primitives.cpp
)
add_executable(PaddleGame
    src/PaddleGame.cpp
)
target_link_libraries(primitives
    PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    OpenGL::GL
    glad_gl_core_33
)
target_link_libraries(PaddleGame
    PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    OpenGL::GL
    glad_gl_core_33
)


target_link_libraries(main
    PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    OpenGL::GL
    glad_gl_core_33
)