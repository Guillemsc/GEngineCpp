cmake_minimum_required(VERSION 3.27)
project(GEngineExternal)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(spdlog)

add_library(GEngineExternal INTERFACE)

target_link_libraries(GEngineExternal INTERFACE spdlog)

target_include_directories(GEngineExternal INTERFACE spdlog/include)