# Main config
cmake_minimum_required(VERSION 3.29)
project(SceneKeeper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# FetchContent Dependencies
set(FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/_deps)

set(RAYLIB_VERSION "5.5")
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG ${RAYLIB_VERSION}
)

set(JSON_VERSION "v3.12.0")
FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG ${JSON_VERSION}
)

FetchContent_MakeAvailable(raylib)
FetchContent_MakeAvailable(nlohmann_json)

# Subdirectories
add_subdirectory(src/viewer)
