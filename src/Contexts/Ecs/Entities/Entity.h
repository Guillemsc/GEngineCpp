//
// Created by Guillem on 31/01/2024.
//

#ifndef GENGINEGAME_ENTITY_H
#define GENGINEGAME_ENTITY_H

#include <iostream>
#include <vector>
#include <memory>
#include <optional>

#include "Utils/Events/Event.h"
#include "Contexts/Ecs/Enums/EntityType.h"

namespace GEngine
{
    class Engine;

    class Entity : public std::enable_shared_from_this<Entity>
    {
        friend class EcsModule;

    public:
        Entity(const Engine* engine);
        virtual ~Entity() = default;

        void Dispose();

        void SetName(const std::string& name);
        EntityType GetType() const;

        void SetParent(const std::shared_ptr<Entity>& parent);
        void RemoveParent();
        std::optional<std::shared_ptr<Entity>> GetParent() const;

        void AddChild(const std::shared_ptr<Entity>& child);
        [[nodiscard]] std::vector<std::shared_ptr<Entity>> GetChilds() const;
        [[nodiscard]] bool IsEntityOnChildHierarchy(const std::shared_ptr<Entity>& parent) const;

        template <typename T>
        std::optional<std::shared_ptr<T>> GetFirstParentOfType();

        void SetActive(bool active);
        [[nodiscard]] bool IsActiveOnTree() const;

    protected:
        explicit Entity(const Engine* engine, EntityType type);

    private:
        void SetOnTree(bool onTree);
        void SetActiveOnTree(bool activeOnTree);
        void Tick();

    protected:
        const Engine* _engine = nullptr;

        Event _enterTreeEvent;
        Event _exitTreeEvent;
        Event _activatedOnTreeEvent;
        Event _deactivatedOnTreeEvent;
        Event _tickEvent;
        Event _parentChangedEvent;

    private:
        std::string _name = "Entity";
        EntityType _type = EntityType::BASE;

        std::optional<std::shared_ptr<Entity>> _parent;
        std::vector<std::shared_ptr<Entity>> _childs;

        bool _onTree = false;
        bool _active = true;
        bool _activeOnTree = false;

        bool _locked = false;
        bool _disposed = false;
    };
}

#include "Contexts/Ecs/Entities/Entity.tpp"

#endif //GENGINEGAME_ENTITY_H
