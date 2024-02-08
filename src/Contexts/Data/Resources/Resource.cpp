//
// Created by Guillem on 02/02/2024.
//

#include "Resource.h"

namespace GEngine
{
    Resource::Resource(const Engine* engine, ResourceType resourceType, const ResourceOrigin &resourceOrigin)
    : _engine(engine), _resourceType(resourceType), _resourceOrigin(resourceOrigin)
    {

    }

    ResourceType Resource::GetResourceType() const
    {
        return _resourceType;
    }

    ResourceOrigin Resource::GetResourceOrigin() const
    {
        return _resourceOrigin;
    }

    bool Resource::GetCanBeUnloaded() const
    {
        return _canBeUnloaded;
    }

    void Resource::SetCanBeUnloaded(bool set)
    {
        _canBeUnloaded = set;
    }
} // GEngine