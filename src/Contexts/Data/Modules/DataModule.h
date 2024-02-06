//
// Created by Guillem on 06/02/2024.
//

#ifndef GENGINEGAME_DATAMODULE_H
#define GENGINEGAME_DATAMODULE_H

#include "Contexts/General/Modules/Module.h"

#include <string>
#include <map>
#include <vector>

#include "Contexts/Data/Resources/StandardMaterialResource.h"
#include "Contexts/Data/ResourceOrigin/InternalResourceOrigin.h"


namespace GEngine
{
    class TextureResource;
    class StandardMaterialResource;
    class MeshResource;

    class DataModule : public Module
    {
    public:
        explicit DataModule(const Engine* engine);

        [[nodiscard]] const StandardMaterialResource& GetDefaultMaterial() const;

        TextureResource& LoadTextureResource(const std::string& filepath);
        void UnloadTextureResource(TextureResource& textureResource);

        StandardMaterialResource& CreateStandardMaterial();

        MeshResource& LoadMeshResource(const std::string& filepath);

    private:
        void Dispose() override;

        void AddResource(const std::shared_ptr<Resource>& resource);
        void UnloadResource(Resource& resource);

    private:
        std::map<ResourceType, std::vector<std::shared_ptr<Resource>>> _resources;

        StandardMaterialResource _defaultMaterial = StandardMaterialResource(InternalResourceOrigin());
    };
} // GEngine

#endif //GENGINEGAME_DATAMODULE_H
