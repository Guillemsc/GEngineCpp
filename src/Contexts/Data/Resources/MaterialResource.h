//
// Created by Guillem on 02/02/2024.
//

#ifndef GENGINEGAME_MATERIALRESOURCE_H
#define GENGINEGAME_MATERIALRESOURCE_H

#include "Contexts/Data/Resources/Resource.h"
#include "Contexts/Data/Enums/MaterialResourceType.h"

namespace GEngine
{
    class MaterialResource : public Resource
    {
    public:
        explicit MaterialResource(const ResourceOrigin& resourceOrigin, MaterialResourceType materialType);
        [[nodiscard]] MaterialResourceType GetMaterialType() const;

    private:
        MaterialResourceType _materialType;
    };

} // GEngine

#endif //GENGINEGAME_MATERIALRESOURCE_H
