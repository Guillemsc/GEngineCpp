//
// Created by Guillem on 01/02/2024.
//

#ifndef GENGINEGAME_BOXPRIMITIVERENDERER3D_H
#define GENGINEGAME_BOXPRIMITIVERENDERER3D_H

#include "Contexts/Ecs/Entities/MeshRenderer3D.h"

namespace GEngine
{
    class Engine;

    class BoxPrimitiveRenderer3D : public MeshRenderer3D
    {
    public:
        explicit BoxPrimitiveRenderer3D(const Engine* engine);

    private:
        void RefreshMesh();

    private:
        Vector3 _size = {1, 1, 1};
    };
} // GEngine

#endif //GENGINEGAME_BOXPRIMITIVERENDERER3D_H
