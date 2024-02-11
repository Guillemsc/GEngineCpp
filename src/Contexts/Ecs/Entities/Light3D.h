//
// Created by Guillem on 08/02/2024.
//

#ifndef GENGINEGAME_LIGHT3D_H
#define GENGINEGAME_LIGHT3D_H

#include "Contexts/Ecs/Entities/Entity3D.h"

namespace GEngine
{
    class Light3D : public Entity3D
    {
    public:
        void SetColor(Color color);
        Color GetColor();

    protected:
        explicit Light3D(const Engine* engine, EntityType entityType);

    private:
        Color _color = WHITE;
    };
} // GEngine

#endif //GENGINEGAME_LIGHT3D_H
