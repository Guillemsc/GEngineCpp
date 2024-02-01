//
// Created by Guillem on 31/01/2024.
//

#include "Entity.h"
#include <algorithm>

namespace GEngine
{
    Entity::Entity(const Engine* engine)
    {
        _engine = engine;
    }

    Entity::Entity(const Engine* engine, EntityType type)
    {
        _engine = engine;
        _type = type;
    }

    void Entity::Dispose()
    {
        if(_locked)
        {
            return;
        }

        std::vector<std::shared_ptr<Entity>> toCheck;
        toCheck.push_back(shared_from_this());

        while(!toCheck.empty())
        {
            std::shared_ptr<Entity> checking = toCheck.front();

            checking->RemoveParent();

            toCheck.erase(toCheck.begin());

            for (const std::shared_ptr<Entity>& child : checking->_childs)
            {
                toCheck.push_back(child);
            }

            checking->_childs.clear();
            checking->_parent.reset();
            checking->_enterTreeEvent.Clear();
            checking->_exitTreeEvent.Clear();
            checking->_disposed = true;
        }
    }

    void Entity::SetName(const std::string& name)
    {
        _name = name;
    }

    EntityType Entity::GetType() const
    {
        return _type;
    }

    void Entity::SetParent(const std::shared_ptr<Entity>& parent)
    {
        if(parent->_disposed || _disposed || _locked)
        {
            return;
        }

        bool isOnChildHierarchy = IsEntityOnChildHierarchy(parent);

        if(isOnChildHierarchy)
        {
            return;
        }

        if(_parent.has_value())
        {
            const std::shared_ptr<Entity>& previousParent = _parent.value();

            bool isSameParent = previousParent == parent;

            if(isSameParent)
            {
                return;
            }

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

        _parentChangedEvent.Trigger();

        SetOnTree(parent->_onTree);
        SetActiveOnTree(parent->_activeOnTree);
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

        _parent.reset();

        _parentChangedEvent.Trigger();

        SetActiveOnTree(false);
        SetOnTree(false);
    }

    std::optional<std::shared_ptr<Entity>> Entity::GetParent() const
    {
        return _parent;
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
        if(_disposed)
        {
            return;
        }

        child->SetParent(shared_from_this());
    }

    std::vector<std::shared_ptr<Entity>> Entity::GetChilds() const
    {
        return _childs;
    }

    void Entity::SetActive(bool active)
    {
        if(_locked || _disposed)
        {
            return;
        }

        _active = active;
        SetActiveOnTree(_active);
    }

    bool Entity::IsActiveOnTree() const
    {
        return _activeOnTree;
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
            toCheck.erase(toCheck.begin());

            bool stateChanged = checking->_onTree != onTree;

            if(!stateChanged)
            {
                continue;
            }

            checking->_onTree = onTree;

            if(checking->_onTree)
            {
                checking->_enterTreeEvent.Trigger();
            }
            else
            {
                checking->_exitTreeEvent.Trigger();
            }

            for (const std::shared_ptr<Entity>& child : checking->_childs)
            {
                toCheck.push_back(child.get());
            }
        }
    }

    void Entity::SetActiveOnTree(bool activeOnTree)
    {
        if(_activeOnTree == activeOnTree)
        {
            return;
        }

        bool cannotActivate = activeOnTree && !_onTree;

        if(cannotActivate)
        {
            return;
        }

        std::vector<Entity*> toCheck;
        toCheck.push_back(this);

        while(!toCheck.empty())
        {
            Entity* checking = toCheck.front();
            toCheck.erase(toCheck.begin());

            bool parentActive = _active;

            if(checking->_parent.has_value())
            {
                parentActive = checking->_parent->get()->_activeOnTree;
            }

            bool newState = parentActive && checking->_active;
            bool stateChanged = newState != checking->_activeOnTree;

            if(!stateChanged)
            {
                continue;
            }

            checking->_activeOnTree = newState;

            if(newState)
            {
                _activatedOnTreeEvent.Trigger();
            }
            else
            {
                _deactivatedOnTreeEvent.Trigger();
            }

            for (const std::shared_ptr<Entity>& child : checking->_childs)
            {
                toCheck.push_back(child.get());
            }
        }
    }

    void Entity::Tick()
    {
        _tickEvent.Trigger();
    }
} // GEngine