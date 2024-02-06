//
// Created by Guillem on 06/02/2024.
//

#include "StandardMaterialResource.h"

#include <functional>

#include "Contexts/Data/Resources/TextureResource.h"

namespace GEngine
{

    StandardMaterialResource::StandardMaterialResource(const ResourceOrigin &resourceOrigin)
        : MaterialResource(resourceOrigin, MaterialResourceType::STANDARD)
    {

    }

    void StandardMaterialResource::SetAlbedoColor(Color color)
    {
        _abledoColor = color;
    }

    Color StandardMaterialResource::GetAlbedoColor() const
    {
        return _abledoColor;
    }

    void StandardMaterialResource::SetAlbedoTexture(GEngine::TextureResource& texture)
    {
        _albedoTexture = texture;
    }

    std::optional<std::reference_wrapper<TextureResource>> StandardMaterialResource::GetAlbedoTexture() const
    {
        return _albedoTexture;
    }
} // GEngine