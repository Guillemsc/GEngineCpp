cmake_minimum_required(VERSION 3.27)
project(GEngine)

set(CMAKE_CXX_STANDARD 17)

add_library(GEngine
        src/Engine.cpp
        src/Engine.h)

target_include_directories(GEngine PUBLIC src)