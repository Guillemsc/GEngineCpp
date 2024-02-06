//
// Created by Guillem on 06/02/2024.
//

#include "MeshResource.h"

namespace GEngine
{
    MeshResource::MeshResource(const ResourceOrigin &resourceOrigin) : Resource(ResourceType::MESH, resourceOrigin)
    {

    }

    std::optional<Mesh> MeshResource::GetMesh() const
    {
       return _mesh;
    }

    void MeshResource::SetMesh(const Mesh &mesh)
    {
        _mesh = mesh;
    }
} // Gengine