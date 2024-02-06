//
// Created by Guillem on 02/02/2024.
//

#ifndef GENGINEGAME_RESOURCE_H
#define GENGINEGAME_RESOURCE_H

#include "Contexts/Data/ResourceOrigin/ResourceOrigin.h"
#include "Contexts/Data/Enums/ResourceType.h"

namespace GEngine
{
    class Resource
    {
    public:
        explicit Resource(ResourceType resourceType, const ResourceOrigin& resourceOrigin);

        ResourceType GetResourceType() const;


    private:
        ResourceType _resourceType;
        ResourceOrigin _resourceOrigin;
    };
} // GEngine

#endif //GENGINEGAME_RESOURCE_H
