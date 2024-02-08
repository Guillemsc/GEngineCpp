//
// Created by Guillem on 06/02/2024.
//

#include "ChildResourceOrigin.h"
#include "Contexts/Data/Resources/Resource.h"

namespace GEngine
{
    ChildResourceOrigin::ChildResourceOrigin(Resource &parent) : ResourceOrigin(ResourceOriginType::CHILD), _parent(parent)
    {

    }
} // GEngine