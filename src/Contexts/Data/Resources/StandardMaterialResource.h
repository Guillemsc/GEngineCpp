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
    class ShaderResource;

    class StandardMaterialResource : public MaterialResource
    {
        friend class DataModule;

    public:
        explicit StandardMaterialResource(const Engine* engine, const ResourceOrigin& resourceOrigin);

        // uniform vec4 colDiffuse
        void SetAlbedoColor(Color color);
        [[nodiscard]] Color GetAlbedoColor() const;

        void SetAlbedoTexture(TextureResource& texture);
        [[nodiscard]] std::optional<std::reference_wrapper<TextureResource>> GetAlbedoTexture() const;

        void SetMetallnessColor(Color color);
        [[nodiscard]] Color GetMetallnessColor() const;

        void SetMetallnessTexture(TextureResource& texture);
        [[nodiscard]] std::optional<std::reference_wrapper<TextureResource>> GetMetallnessTexture() const;

    protected:
        void CopyStandardMaterialTo(StandardMaterialResource& other) const;

    private:
        Color _abledoColor = WHITE;
        std::optional<std::reference_wrapper<TextureResource>> _albedoTexture;

        Color _metallnessColor = WHITE;
        std::optional<std::reference_wrapper<TextureResource>> _metallnessTexture;
    };
} // GEngine

#endif //GENGINEGAME_STANDARDMATERIALRESOURCE_H
