//
// Created by Guillem on 06/02/2024.
//

#include "TextureResource.h"

namespace GEngine
{
    TextureResource::TextureResource(const Engine* engine, const ResourceOrigin &resourceOrigin)
        : Resource(engine, ResourceType::TEXTURE, resourceOrigin)
    {

    }

    std::optional<Texture> TextureResource::GetTexture() const
    {
        return _texture;
    }

    void TextureResource::SetTexture(const Texture &texture)
    {
        _texture = texture;
    }
} // GEngine