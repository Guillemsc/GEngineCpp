//
// Created by Guillem on 01/02/2024.
//

#include "BoxPrimitiveRenderer3D.h"

#include "Core/Engine.h"
#include "Contexts/Data/Modules/DataModule.h"
#include "Contexts/Data/Resources/MeshResource.h"

namespace GEngine
{
    BoxPrimitiveRenderer3D::BoxPrimitiveRenderer3D(const Engine *engine, EntityType entityType)
        : MeshRenderer3D(engine, entityType)
    {
        RefreshMesh();
    }

    void BoxPrimitiveRenderer3D::RefreshMesh()
    {
        Mesh mesh = GenMeshCube(_size.x, _size.y, _size.z);

        std::optional<std::reference_wrapper<MeshResource>> optionalMesh = GetMesh();

        if(!optionalMesh.has_value())
        {
            MeshResource& meshResource = _engine->GetData().CreateMeshResource(InternalResourceOrigin());
            SetMeshInternal(meshResource);
            optionalMesh = meshResource;
        }

        _engine->GetData().RefreshMeshResource(optionalMesh->get(), mesh);
    }
} // GEngine