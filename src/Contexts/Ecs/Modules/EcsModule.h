//
// Created by Guillem on 31/01/2024.
//

#ifndef GENGINEGAME_ECSMODULE_H
#define GENGINEGAME_ECSMODULE_H

#include "Contexts/General/Modules/Module.h"

#include <vector>
#include <memory>
#include <string>

#include "Contexts/Ecs/Enums/EntityType.h"

namespace GEngine
{
    class Entity;
    class Entity3D;

    class EcsModule : public Module
    {
    public:
        explicit EcsModule(const Engine* engine);

        [[nodiscard]] std::shared_ptr<Entity> GetRoot() const;

        std::shared_ptr<Entity> Create(EntityType entityType, const std::string& name = "Entity");
        template<typename T>
        std::shared_ptr<T> Create(EntityType entityType, const std::string& name = "Entity");
        template<typename T>
        std::shared_ptr<T> Create(const std::string& name = "Entity");

    protected:
        void Init() override;
        void Tick() override;
        void Dispose() override;

    private:
        void TickEntities();

        std::shared_ptr<Entity> CreateByType(EntityType entityType);

    private:
        std::shared_ptr<Entity> _rootEntity;
    };

} // GEngine

#include "Contexts/Ecs/Modules/EcsModule.tpp"

#endif //GENGINEGAME_ECSMODULE_H
