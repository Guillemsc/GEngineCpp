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
        src/Contexts/Renderer3D/RenderQueue/RenderQueue3D.cpp
        src/Contexts/Renderer3D/RenderQueue/RenderQueue3D.h
        src/Contexts/Renderer3D/RenderQueue/DrawCall.cpp
        src/Contexts/Renderer3D/RenderQueue/DrawCall.h
        src/Contexts/General/Modules/Module.cpp
        src/Contexts/Ecs/Entities/BoxPrimitiveRenderer3D.cpp
        src/Contexts/Ecs/Entities/BoxPrimitiveRenderer3D.h
        src/Contexts/Ecs/Entities/MeshRenderer3D.cpp
        src/Contexts/Ecs/Entities/MeshRenderer3D.h
        src/Contexts/Data/Resources/Resource.cpp
        src/Contexts/Data/Resources/Resource.h
        src/Contexts/Data/ResourceOrigin/ResourceOrigin.cpp
        src/Contexts/Data/ResourceOrigin/ResourceOrigin.h
        src/Contexts/Data/Resources/MaterialResource.cpp
        src/Contexts/Data/Resources/MaterialResource.h
        src/Contexts/Data/Enums/MaterialResourceType.h
        src/Contexts/Data/Modules/DataModule.cpp
        src/Contexts/Data/Modules/DataModule.h
        src/Contexts/Data/Resources/StandardMaterialResource.cpp
        src/Contexts/Data/Resources/StandardMaterialResource.h
        src/Contexts/Data/ResourceOrigin/InternalResourceOrigin.cpp
        src/Contexts/Data/ResourceOrigin/InternalResourceOrigin.h
        src/Contexts/Data/Resources/TextureResource.cpp
        src/Contexts/Data/Resources/TextureResource.h
        src/Contexts/Data/ResourceOrigin/FileSystemResourceOrigin.cpp
        src/Contexts/Data/ResourceOrigin/FileSystemResourceOrigin.h
        src/Contexts/Data/Enums/ResourceType.h
        src/Contexts/Data/Resources/MeshResource.cpp
        src/Contexts/Data/Resources/MeshResource.h
        src/Contexts/Data/Resources/ModelResource.cpp
        src/Contexts/Data/Resources/ModelResource.h
        src/Contexts/Data/ResourceOrigin/ChildResourceOrigin.cpp
        src/Contexts/Data/ResourceOrigin/ChildResourceOrigin.h
        src/Utils/Extensions/MapExtensions.cpp
        src/Utils/Extensions/MapExtensions.h
        src/Utils/Extensions/MapExtensions.tpp
        src/Contexts/Data/Enums/ResourceOriginType.h
        src/Contexts/Ecs/Entities/MeshResourceRenderer3D.cpp
        src/Contexts/Ecs/Entities/MeshResourceRenderer3D.h
        src/Contexts/Data/Resources/ShaderResource.cpp
        src/Contexts/Data/Resources/ShaderResource.h
        src/Contexts/Data/ResourceOrigin/CopyResourceOrigin.cpp
        src/Contexts/Data/ResourceOrigin/CopyResourceOrigin.h
        src/Contexts/Renderer3D/Enums/BaseShaderUniformLocations.h
        src/Contexts/Renderer3D/Enums/Light3DType.h
        src/Contexts/Ecs/Entities/Light3D.cpp
        src/Contexts/Ecs/Entities/Light3D.h
        src/Contexts/Ecs/Entities/DirectionalLight3D.cpp
        src/Contexts/Ecs/Entities/DirectionalLight3D.h
        src/Contexts/Game/Modules/GameModule.cpp
        src/Contexts/Game/Modules/GameModule.h
        src/Contexts/Game/Modules/GameModule.h
        src/Contexts/Game/Games/Game.cpp
        src/Contexts/Game/Games/Game.h
        src/Contexts/Ecs/Entities/AxisRenderer3D.cpp
        src/Contexts/Ecs/Entities/AxisRenderer3D.h
)

add_subdirectory(external)

target_link_libraries(gengine gengine_external)

target_include_directories(gengine PUBLIC src)