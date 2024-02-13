//
// Created by Guillem on 13/02/2024.
//

#ifndef GENGINEGAME_AXISRENDERER3D_H
#define GENGINEGAME_AXISRENDERER3D_H

#include "Contexts/Ecs/Entities/Entity3D.h"

namespace GEngine
{
    class AxisRenderer3D : public Entity3D
    {
    public:
        explicit AxisRenderer3D(const Engine* engine, EntityType entityType);

        void SetAxisLenght(float lenght);

    private:
        void WhenTick();
        void Render(const Camera3D& camera);

    private:
        float _axisLenght = 2;
    };
} // GEngine

#endif //GENGINEGAME_AXISRENDERER3D_H
