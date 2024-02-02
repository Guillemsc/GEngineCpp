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

    class MeshRenderer3D : public Entity3D
    {
    public:
        explicit MeshRenderer3D(const Engine* engine);

    protected:
        void SetMesh(const Mesh& mesh);
        void ClearMesh();

    private:
        void Tick();
        void Render();

    private:
        std::optional<Model> _model;
    };
}


#endif //GENGINEGAME_MESHRENDERER3D_H
