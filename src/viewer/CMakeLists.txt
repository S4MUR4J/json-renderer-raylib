cmake_minimum_required(VERSION 3.29)
project(viewer LANGUAGES CXX)

file(GLOB_RECURSE VIEWER_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)

add_executable(viewer ${VIEWER_SOURCES})

target_include_directories(viewer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(viewer
    PRIVATE
        raylib
        nlohmann_json
)

target_compile_options(viewer PRIVATE
    -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror
)

if (UNIX)
    target_link_libraries(viewer PRIVATE m pthread dl)
endif()