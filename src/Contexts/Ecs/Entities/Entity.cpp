//
// Created by Guillem on 31/01/2024.
//

#include "Entity.h"
#include <algorithm>
#include <utility>

namespace GEngine
{
    std::shared_ptr<Entity> Entity::Create()
    {
        return std::make_shared<Entity>();
    }

    std::shared_ptr<Entity> Entity::Create(const std::string &name)
    {
        const std::shared_ptr<Entity>& newEntity = Create();
        newEntity->SetName(name);
        return newEntity;
    }

    void Entity::Dispose()
    {
        _childs.clear();
        _parent.reset();
    }

    void Entity::SetName(const std::string& name)
    {
        _name = name;
    }

    void Entity::SetParent(const std::shared_ptr<Entity>& parent)
    {
        bool isOnChildHierarchy = IsEntityOnChildHierarchy(parent);

        if(isOnChildHierarchy)
        {
            return;
        }

        if(_parent.has_value())
        {
            const std::shared_ptr<Entity>& previousParent = _parent.value();

            for(auto it = previousParent->_childs.begin(); it != previousParent->_childs.end() ; ++it)
            {
                if((*it).get() == this)
                {
                    previousParent->_childs.erase(it);
                    break;
                }
            }
        }

        parent->_childs.push_back(shared_from_this());
        this->_parent = parent;

        SetOnTree(parent->_onTree);
    }

    void Entity::RemoveParent()
    {
        if(!_parent.has_value())
        {
            return;
        }

        const std::shared_ptr<Entity>& parent = _parent.value();

        for(auto it = parent->_childs.begin(); it != parent->_childs.end() ; ++it)
        {
            if((*it).get() == this)
            {
                parent->_childs.erase(it);
                break;
            }
        }

        _parent->reset();

        SetOnTree(false);
    }

    bool Entity::IsEntityOnChildHierarchy(const std::shared_ptr<Entity>& entity) const
    {
        std::vector<const Entity*> toCheck;
        toCheck.push_back(this);

        while(!toCheck.empty())
        {
            const Entity* checking = toCheck.front();

            if(checking == entity.get())
            {
                return true;
            }

            toCheck.erase(toCheck.begin());

            for (const std::shared_ptr<Entity>& child : checking->_childs)
            {
                toCheck.push_back(child.get());
            }
        }

        return false;
    }

    void Entity::AddChild(const std::shared_ptr<Entity> &child)
    {
        child->SetParent(shared_from_this());
    }

    void Entity::SetOnTree(bool onTree)
    {
        if(onTree == _onTree)
        {
            return;
        }

        std::vector<Entity*> toCheck;
        toCheck.push_back(this);

        while(!toCheck.empty())
        {
            Entity* checking = toCheck.front();

            checking->_onTree = onTree;

            toCheck.erase(toCheck.begin());

            for (const std::shared_ptr<Entity>& child : checking->_childs)
            {
                toCheck.push_back(child.get());
            }
        }
    }
} // GEngine