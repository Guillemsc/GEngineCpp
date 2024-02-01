//
// Created by Guillem on 31/01/2024.
//

#ifndef GENGINEGAME_ENTITY_H
#define GENGINEGAME_ENTITY_H

#include <iostream>
#include <vector>
#include <memory>
#include <optional>
#include "Contexts/Ecs/Components/Component.h"
#include "Contexts/Ecs/Constants/ComponentsConstants.h"

class EcsModule;

namespace GEngine
{
    class Entity : public std::enable_shared_from_this<Entity>
    {
        friend class EcsModule;

    public:
        static std::shared_ptr<Entity> Create();
        static std::shared_ptr<Entity> Create(const std::string& name);

    public:
        void Dispose();

        void SetName(const std::string& name);

        void SetParent(const std::shared_ptr<Entity>& parent);
        void RemoveParent();
        void AddChild(const std::shared_ptr<Entity>& child);
        [[nodiscard]] bool IsEntityOnChildHierarchy(const std::shared_ptr<Entity>& parent) const;

    private:
        void SetOnTree(bool onTree);

    private:
        std::string _name = "Entity";

        std::optional<std::shared_ptr<Entity>> _parent;
        std::vector<std::shared_ptr<Entity>> _childs;

        bool _onTree = false;
    };
}


#endif //GENGINEGAME_ENTITY_H
