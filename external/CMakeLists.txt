cmake_minimum_required(VERSION 3.27)
project(gengine_external)

set(CMAKE_CXX_STANDARD 17)

add_library(gengine_external INTERFACE)

add_subdirectory(spdlog)
add_subdirectory(raylib)

target_link_libraries(gengine_external INTERFACE spdlog)
target_link_libraries(gengine_external INTERFACE raylib)

# RAYLIB START -----
# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

if (APPLE)
    target_link_libraries(gengine_external "-framework IOKit")
    target_link_libraries(gengine_external "-framework Cocoa")
    target_link_libraries(gengine_external "-framework OpenGL")
endif()
# RAYLIB END ------

target_include_directories(gengine_external INTERFACE spdlog/include)
target_include_directories(gengine_external INTERFACE raylib/src)
