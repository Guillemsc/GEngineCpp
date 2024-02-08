//
// Created by Guillem on 06/02/2024.
//

#ifndef GENGINEGAME_TEXTURERESOURCE_H
#define GENGINEGAME_TEXTURERESOURCE_H

#include "Contexts/Data/Resources/Resource.h"

#include <optional>
#include "raylib.h"

namespace GEngine
{
    class DataModule;

    class TextureResource : public Resource
    {
        friend DataModule;

    public:
        explicit TextureResource(const Engine* engine, const ResourceOrigin& resourceOrigin);

        [[nodiscard]] std::optional<Texture2D> GetTexture() const;

    private:
        void SetTexture(const Texture& texture);

    private:
        std::optional<Texture> _texture;
    };
} // GEngine

#endif //GENGINEGAME_TEXTURERESOURCE_H
