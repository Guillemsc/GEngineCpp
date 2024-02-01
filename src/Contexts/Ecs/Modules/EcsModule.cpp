//
// Created by Guillem on 31/01/2024.
//

#include "EcsModule.h"

#include "Contexts/Ecs/Entities/Entity.h"
#include "Contexts/Ecs/Entities/Entity3D.h"
#include "Contexts/Ecs/Entities/PrimitiveRenderer3D.h"

namespace GEngine
{
    EcsModule::EcsModule(const Engine* engine) : Module(engine)
    {
        _rootEntity = Create(EntityType::BASE, "Root");
        _rootEntity->_activeOnTree = true;
        _rootEntity->_onTree = true;
        _rootEntity->_locked = true;
    }

    EcsModule::~EcsModule()
    {
        _rootEntity->_locked = false;
        _rootEntity->Dispose();
    }

    void EcsModule::Tick()
    {
        TickEntities();
    }

    std::shared_ptr<Entity> EcsModule::GetRoot() const
    {
        return _rootEntity;
    }

    std::shared_ptr<Entity> EcsModule::Create(EntityType entityType, const std::string &name)
    {
        const std::shared_ptr<Entity>& entity = CreateByType(entityType);
        entity->SetName(name);
        return entity;
    }

    template<>
    std::shared_ptr<Entity> GEngine::EcsModule::Create<GEngine::Entity>(const std::string &name)
    {
        return Create<Entity>(EntityType::BASE, name);
    }

    template<>
    std::shared_ptr<Entity3D> GEngine::EcsModule::Create<Entity3D>(const std::string &name)
    {
        return Create<Entity3D>(EntityType::ENTITY_3D, name);
    }

    template<>
    std::shared_ptr<PrimitiveRenderer3D> GEngine::EcsModule::Create<PrimitiveRenderer3D>(const std::string &name)
    {
        return Create<PrimitiveRenderer3D>(EntityType::PRIMITIVE_RENDERER_3D, name);
    }

    void EcsModule::TickEntities()
    {
        std::vector<Entity*> toCheck;
        toCheck.push_back(_rootEntity.get());

        while(!toCheck.empty())
        {
            Entity* checking = toCheck.front();
            toCheck.erase(toCheck.begin());

            checking->Tick();

            for (const std::shared_ptr<Entity>& child : checking->_childs)
            {
                toCheck.push_back(child.get());
            }
        }
    }

    std::shared_ptr<Entity> GEngine::EcsModule::CreateByType(EntityType entityType)
    {
        switch(entityType)
        {
            case BASE:
            {
                return std::make_shared<Entity>(_engine);
            }
            case ENTITY_3D:
            {
                return std::make_shared<Entity3D>(_engine);
            }
            case PRIMITIVE_RENDERER_3D:
            {
                return std::make_shared<PrimitiveRenderer3D>(_engine);
            }
            default:
            {
                throw std::runtime_error("Missing implementation");
            }
        }
    }

} // GEngine