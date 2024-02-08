//
// Created by Guillem on 02/02/2024.
//

#ifndef GENGINEGAME_RESOURCEORIGIN_H
#define GENGINEGAME_RESOURCEORIGIN_H

#include "Contexts/Data/Enums/ResourceOriginType.h"

namespace GEngine
{
    class ResourceOrigin
    {
    public:
        explicit ResourceOrigin(ResourceOriginType resourceOriginType);

    private:
        const ResourceOriginType _resourceOriginType;
    };

} // GEngine

#endif //GENGINEGAME_RESOURCEORIGIN_H
