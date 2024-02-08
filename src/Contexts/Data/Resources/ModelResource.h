//
// Created by Guillem on 06/02/2024.
//

#ifndef GENGINEGAME_MODELRESOURCE_H
#define GENGINEGAME_MODELRESOURCE_H

#include "Contexts/Data/Resources/Resource.h"

#include <vector>
#include <optional>

#include "raylib.h"

namespace GEngine
{
    class DataModule;
    class MeshResource;
    class StandardMaterialResource;

    class ModelResource : public Resource
    {
        friend class DataModule;

    public:
        explicit ModelResource(const Engine* engine, const ResourceOrigin& resourceOrigin);

        [[nodiscard]] MeshResource& GetMesh(int index) const;
        [[nodiscard]] StandardMaterialResource& GetMaterialCopy(int index) const;

    private:
        [[nodiscard]] std::optional<Model> GetModel() const;
        void SetModel(const Model& mesh);

        void AddMesh(MeshResource& mesh);
        void AddMaterial(StandardMaterialResource& material);

    private:
        std::vector<MeshResource*> _meshes;
        std::vector<StandardMaterialResource*> _materials;

        std::optional<Model> _model;
    };
} // GEngine

#endif //GENGINEGAME_MODELRESOURCE_H
