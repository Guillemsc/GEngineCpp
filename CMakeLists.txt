cmake_minimum_required(VERSION 3.27)
project(gengine)

set(CMAKE_CXX_STANDARD 17)

add_library(gengine
        src/Bootstraps/GEngineBootstrap.cpp
        src/Bootstraps/GEngineBootstrap.h
        src/Contexts/General/Module.h
        src/Contexts/Ecs/Modules/EcsModule.cpp
        src/Contexts/Ecs/Modules/EcsModule.h
        src/Contexts/Ecs/Entities/Entity.cpp
        src/Contexts/Ecs/Entities/Entity.h
        src/Contexts/Ecs/Components/Component.h
        src/Contexts/Ecs/Enums/ComponentType.h
        src/Contexts/Ecs/Constants/ComponentsConstants.h)

add_subdirectory(external)

target_link_libraries(gengine gengine_external)

target_include_directories(gengine PUBLIC src)