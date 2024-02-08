//
// Created by Guillem on 06/02/2024.
//

#include "ModelResource.h"

#include "Core/Engine.h"
#include "Contexts/Data/Modules/DataModule.h"

namespace GEngine
{
    ModelResource::ModelResource(const Engine* engine, const ResourceOrigin &resourceOrigin)
        : Resource(engine, ResourceType::MODEL, resourceOrigin)
    {

    }

    MeshResource& ModelResource::GetMesh(int index) const
    {
        return *_meshes[index];
    }

    StandardMaterialResource& ModelResource::GetMaterialCopy(int index) const
    {
        StandardMaterialResource& materialResource =  *_materials[index];

        return _engine->GetData().DuplicateStandardMaterialResource(materialResource);
    }

    void ModelResource::AddMesh(MeshResource &mesh)
    {
        _meshes.push_back(&mesh);
    }

    void ModelResource::AddMaterial(StandardMaterialResource &material)
    {
        _materials.push_back(&material);
    }

    std::optional<Model> ModelResource::GetModel() const
    {
        return _model;
    }

    void ModelResource::SetModel(const Model &model)
    {
        _model = model;
    }

} // GEngine