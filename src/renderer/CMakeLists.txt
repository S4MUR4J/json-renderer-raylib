cmake_minimum_required(VERSION 3.29)
project(renderer LANGUAGES CXX)

include(FetchContent)
set(FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/_deps)

set(RAYLIB_VERSION "5.5")
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG ${RAYLIB_VERSION}
)

FetchContent_MakeAvailable(raylib)

file(GLOB_RECURSE RENDERER_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(renderer ${RENDERER_SOURCES})

target_include_directories(renderer
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(renderer
    PRIVATE
        raylib
)

target_compile_options(renderer PRIVATE
    -Wall -Wextra -Wpedantic -Werror
)

if (UNIX)
    target_link_libraries(renderer PRIVATE m pthread dl)
endif()