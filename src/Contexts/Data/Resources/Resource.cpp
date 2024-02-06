//
// Created by Guillem on 02/02/2024.
//

#include "Resource.h"

namespace GEngine
{
    Resource::Resource(ResourceType resourceType, const ResourceOrigin &resourceOrigin)
    {
        _resourceType = resourceType;
        _resourceOrigin = resourceOrigin;
    }

    ResourceType Resource::GetResourceType() const
    {
        return _resourceType;
    }
} // GEngine