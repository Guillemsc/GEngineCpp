//
// Created by Guillem on 06/02/2024.
//

#ifndef GENGINEGAME_STANDARDMATERIALRESOURCE_H
#define GENGINEGAME_STANDARDMATERIALRESOURCE_H

#include "Contexts/Data/Resources/MaterialResource.h"
#include "Contexts/Data/ResourceOrigin/ResourceOrigin.h"

#include <memory>
#include <optional>

#include "raylib.h"

namespace GEngine
{
    class TextureResource;

    class StandardMaterialResource : public MaterialResource
    {
    public:
        explicit StandardMaterialResource(const ResourceOrigin& resourceOrigin);

        void SetAlbedoColor(Color color);
        [[nodiscard]] Color GetAlbedoColor() const;

        void SetAlbedoTexture(GEngine::TextureResource& texture);
        [[nodiscard]] std::optional<std::reference_wrapper<TextureResource>> GetAlbedoTexture() const;

    private:
        Color _abledoColor = WHITE;
        std::optional<std::reference_wrapper<TextureResource>> _albedoTexture;
    };
} // GEngine

#endif //GENGINEGAME_STANDARDMATERIALRESOURCE_H
