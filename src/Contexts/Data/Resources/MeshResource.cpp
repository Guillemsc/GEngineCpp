//
// Created by Guillem on 06/02/2024.
//

#include "MeshResource.h"

namespace GEngine
{
    MeshResource::MeshResource(const Engine* engine, const ResourceOrigin &resourceOrigin)
    : Resource(engine, ResourceType::MESH, resourceOrigin)
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