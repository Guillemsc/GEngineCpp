//
// Created by Guillem on 02/02/2024.
//

#ifndef GENGINEGAME_MESHRENDERER3D_H
#define GENGINEGAME_MESHRENDERER3D_H

#include "Contexts/Ecs/Entities/Entity3D.h"

#include <optional>

#include "raylib.h"

namespace GEngine
{
    class Engine;
    class MeshResource;
    class MaterialResource;

    class MeshRenderer3D : public Entity3D
    {
    public:
        explicit MeshRenderer3D(const Engine* engine, EntityType entityType);

        std::optional<std::reference_wrapper<MeshResource>> GetMesh() const;

        void SetMaterial(MaterialResource& materialResource);
        std::optional<std::reference_wrapper<MaterialResource>> GetMaterial() const;

    protected:
        void SetMeshInternal(MeshResource& meshResource);
        void ClearMesh();
        bool HasMesh() const;

    private:
        void Tick();
        void Render(const Camera3D& camera);

    private:
        std::optional<std::reference_wrapper<MeshResource>> _mesh;
        std::optional<std::reference_wrapper<MaterialResource>> _material;
    };
}


#endif //GENGINEGAME_MESHRENDERER3D_H
