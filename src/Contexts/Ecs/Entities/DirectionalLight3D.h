//
// Created by Guillem on 08/02/2024.
//

#ifndef GENGINEGAME_DIRECTIONALLIGHT3D_H
#define GENGINEGAME_DIRECTIONALLIGHT3D_H

#include "Contexts/Ecs/Entities/Light3D.h"

namespace GEngine
{

    class DirectionalLight3D : public Light3D
    {
    public:
        explicit DirectionalLight3D(const Engine* engine, EntityType entityType);
    };

} // GEngine

#endif //GENGINEGAME_DIRECTIONALLIGHT3D_H
