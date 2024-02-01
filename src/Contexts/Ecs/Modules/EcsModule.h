//
// Created by Guillem on 31/01/2024.
//

#ifndef GENGINEGAME_ECSMODULE_H
#define GENGINEGAME_ECSMODULE_H

#include "Contexts/General/Module.h"

#include <vector>
#include <memory>

#include "Contexts/Ecs/Entities/Entity.h"

class Entity;

namespace GEngine
{
    class EcsModule : Module
    {
    public:
        void Add(const std::shared_ptr<Entity> &entity);

    private:
        std::vector<std::shared_ptr<Entity>> _rootEntities;
    };

} // GEngine

#endif //GENGINEGAME_ECSMODULE_H
