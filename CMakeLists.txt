cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Include header files
include_directories(${CMAKE_SOURCE_DIR}/include)

# Gather all .cpp files
add_executable(SnakeBoardGame
    src/main.cpp
    src/game.cpp
    src/player.cpp
    src/dice.cpp
    src/board.cpp
)

target_link_libraries(SnakeBoardGame PRIVATE SFML::Graphics SFML::Window SFML::System)

