//
// Created by Guillem on 02/02/2024.
//

#include "MaterialResource.h"

namespace GEngine
{
    MaterialResource::MaterialResource(const ResourceOrigin &resourceOrigin, MaterialResourceType materialType) : Resource(resourceOrigin)
    {
        _materialType = materialType;
    }

    MaterialResourceType MaterialResource::GetMaterialType() const
    {
        return _materialType;
    }
} // GEngine