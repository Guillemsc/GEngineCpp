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
    class MaterialResource;

    class MeshRenderer3D : public Entity3D
    {
    public:
        explicit MeshRenderer3D(const Engine* engine);

        void SetMaterial(MaterialResource& materialResource);
        std::optional<std::reference_wrapper<MaterialResource>> GetMaterial() const;

    protected:
        void SetMesh(const Mesh& mesh);
        void ClearMesh();

    private:
        void Tick();
        void Render();

    private:
        std::optional<Model> _model;
        std::optional<std::reference_wrapper<MaterialResource>> _materialResource;
    };
}


#endif //GENGINEGAME_MESHRENDERER3D_H
