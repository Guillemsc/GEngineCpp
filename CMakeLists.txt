cmake_minimum_required(VERSION 3.27)
project(gengine)

set(CMAKE_CXX_STANDARD 17)

add_library(gengine
        src/Core/Engine.cpp
        src/Core/Engine.h
        src/Contexts/General/Modules/Module.h
        src/Contexts/Ecs/Modules/EcsModule.cpp
        src/Contexts/Ecs/Modules/EcsModule.h
        src/Contexts/Ecs/Entities/Entity.cpp
        src/Contexts/Ecs/Entities/Entity.h
        src/Contexts/Ecs/Enums/EntityType.h
        src/Utils/Events/Event.h
        src/Contexts/Ecs/Entities/Entity3D.cpp
        src/Contexts/Ecs/Entities/Entity3D.h
        src/Contexts/Ecs/Entities/Entity.tpp
        src/Utils/Extensions/MathExtensions.cpp
        src/Utils/Extensions/MathExtensions.h
        src/Contexts/Window/Modules/WindowModule.cpp
        src/Contexts/Window/Modules/WindowModule.h
        src/Contexts/Renderer3D/Modules/Renderer3DModule.cpp
        src/Contexts/Renderer3D/Modules/Renderer3DModule.h
        src/Contexts/General/RenderQueue/RenderQueue.cpp
        src/Contexts/General/RenderQueue/RenderQueue.h
        src/Contexts/General/RenderQueue/DrawCall.cpp
        src/Contexts/General/RenderQueue/DrawCall.h
        src/Contexts/General/Modules/Module.cpp
        src/Contexts/Ecs/Entities/PrimitiveRenderer3D.cpp
        src/Contexts/Ecs/Entities/PrimitiveRenderer3D.h)

add_subdirectory(external)

target_link_libraries(gengine gengine_external)

target_include_directories(gengine PUBLIC src)