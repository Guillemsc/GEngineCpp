cmake_minimum_required(VERSION 3.27)
project(GEngine)

set(CMAKE_CXX_STANDARD 17)

add_library(GEngine
        src/Engine.cpp
        src/Engine.h)

add_subdirectory(external)

target_link_libraries(GEngine GEngineExternal)

target_include_directories(GEngine PUBLIC src)