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
#include "Contexts/Ecs/Entities/Entity.h"

namespace GEngine
{
    class EcsModule : public Module
    {
    public:
        explicit EcsModule(const Engine* engine);

        [[nodiscard]] std::shared_ptr<Entity> GetRoot() const;

        std::shared_ptr<Entity> Create(EntityType entityType, const std::string& name = "Entity");
        template<typename T>
        std::shared_ptr<T> Create(const std::string& name = "Entity");

        template<typename T>
        std::vector<std::shared_ptr<T>> GetAll() const;

        void DisposeAll();

    protected:
        void Init() override;
        void Tick() override;
        void Dispose() override;

    private:
        template<typename T>
        std::shared_ptr<T> Create(EntityType entityType, const std::string& name = "Entity");

        void TickEntities();

        std::shared_ptr<Entity> CreateByType(EntityType entityType);

    private:
        std::shared_ptr<Entity> _rootEntity;
    };

} // GEngine

#include "Contexts/Ecs/Modules/EcsModule.tpp"

#endif //GENGINEGAME_ECSMODULE_H
