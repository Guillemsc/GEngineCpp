//
// Created by Guillem on 06/02/2024.
//

#include "MeshResourceRenderer3D.h"

namespace GEngine
{
    MeshResourceRenderer3D::MeshResourceRenderer3D(const Engine *engine, EntityType entityType)
        : MeshRenderer3D(engine, entityType)
    {

    }

    void MeshResourceRenderer3D::SetMesh(MeshResource &meshResource)
    {
        SetMeshInternal(meshResource);
    }
} // GEngine