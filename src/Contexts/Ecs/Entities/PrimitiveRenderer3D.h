//
// Created by Guillem on 01/02/2024.
//

#ifndef GENGINEGAME_PRIMITIVERENDERER3D_H
#define GENGINEGAME_PRIMITIVERENDERER3D_H

#include "Contexts/Ecs/Entities/Entity.h"

namespace GEngine
{
    class Engine;

    class PrimitiveRenderer3D : public Entity
    {
    public:
        explicit PrimitiveRenderer3D(const Engine* engine);

    private:
        void Tick();
        void Render();
    };
} // GEngine

#endif //GENGINEGAME_PRIMITIVERENDERER3D_H
