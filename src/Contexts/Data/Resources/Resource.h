//
// Created by Guillem on 02/02/2024.
//

#ifndef GENGINEGAME_RESOURCE_H
#define GENGINEGAME_RESOURCE_H

#include "Contexts/Data/ResourceOrigin/ResourceOrigin.h"

namespace GEngine
{
    class Resource
    {
    public:
        explicit Resource(const ResourceOrigin& resourceOrigin);

    private:
        ResourceOrigin _resourceOrigin;
    };
} // GEngine

#endif //GENGINEGAME_RESOURCE_H
