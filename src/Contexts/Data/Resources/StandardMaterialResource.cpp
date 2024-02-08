//
// Created by Guillem on 06/02/2024.
//

#include "StandardMaterialResource.h"

#include <functional>

#include "Contexts/Data/Resources/TextureResource.h"

namespace GEngine
{

    StandardMaterialResource::StandardMaterialResource(const Engine* engine, const ResourceOrigin &resourceOrigin)
        : MaterialResource(engine, resourceOrigin, MaterialResourceType::STANDARD)
    {
        SetAlbedoColor(PINK);
    }

    void StandardMaterialResource::SetAlbedoColor(Color color)
    {
        _abledoColor = color;
        SetShaderColorValue("colDiffuse", _abledoColor);
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

    void StandardMaterialResource::SetMetallnessColor(Color color)
    {
        _metallnessColor = color;
    }

    Color StandardMaterialResource::GetMetallnessColor() const
    {
        return _metallnessColor;
    }

    void StandardMaterialResource::SetMetallnessTexture(GEngine::TextureResource &texture)
    {
        _metallnessTexture = texture;
    }

    std::optional<std::reference_wrapper<TextureResource>> StandardMaterialResource::GetMetallnessTexture() const
    {
        return _metallnessTexture;
    }

    void StandardMaterialResource::CopyStandardMaterialTo(StandardMaterialResource &other) const
    {
        CopyMaterialTo(other);

        other._abledoColor = _abledoColor;
        other._albedoTexture = _albedoTexture;
        other._metallnessColor = _metallnessColor;
        other._metallnessTexture = _metallnessTexture;
    }
} // GEngine