//
// Created by Guillem on 06/02/2024.
//

#ifndef GENGINEGAME_MESHRESOURCERENDERER3D_H
#define GENGINEGAME_MESHRESOURCERENDERER3D_H

#include "Contexts/Ecs/Entities/MeshRenderer3D.h"

namespace GEngine
{
    class Engine;

    class MeshResourceRenderer3D : public MeshRenderer3D
    {
    public:
        explicit MeshResourceRenderer3D(const Engine* engine, EntityType entityType);

        void SetMesh(MeshResource& meshResource);
    };
} // GEngine

#endif //GENGINEGAME_MESHRESOURCERENDERER3D_H
