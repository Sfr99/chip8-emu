cmake_minimum_required(VERSION 3.16)

project(chip8-emu
  VERSION
    0.2.0
  LANGUAGES
    CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(SDL2 REQUIRED)

file(GLOB SOURCES src/*.cpp)
add_executable(chip8-emu ${SOURCES})
target_include_directories(chip8-emu PRIVATE include)
target_link_libraries(chip8-emu PRIVATE SDL2::SDL2)