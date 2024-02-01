//
// Created by Guillem on 31/01/2024.
//

#include "EcsModule.h"

namespace GEngine
{
    void EcsModule::Add(const std::shared_ptr<Entity> &entity)
    {
        if(entity->_onTree)
        {
            return;
        }

        entity->RemoveParent();

        entity->SetOnTree(true);

        _rootEntities.push_back(entity);
    }
} // GEngine