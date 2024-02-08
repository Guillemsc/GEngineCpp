//
// Created by Guillem on 06/02/2024.
//

#ifndef GENGINEGAME_CHILDRESOURCEORIGIN_H
#define GENGINEGAME_CHILDRESOURCEORIGIN_H

#include "Contexts/Data/ResourceOrigin/ResourceOrigin.h"

namespace GEngine
{
    class Resource;

    class ChildResourceOrigin : public ResourceOrigin
    {
    public:
        explicit ChildResourceOrigin(Resource& parent);

    private:
        const Resource& _parent;
    };

} // GEngine

#endif //GENGINEGAME_CHILDRESOURCEORIGIN_H
