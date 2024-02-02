//
// Created by Guillem on 01/02/2024.
//

#include "BoxPrimitiveRenderer3D.h"

namespace GEngine
{
    BoxPrimitiveRenderer3D::BoxPrimitiveRenderer3D(const Engine *engine) : MeshRenderer3D(engine)
    {
        RefreshMesh();
    }

    void BoxPrimitiveRenderer3D::RefreshMesh()
    {
        Mesh mesh = GenMeshCube(_size.x, _size.y, _size.z);
        SetMesh(mesh);
    }
} // GEngine