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
    class ModelResource;
    class MeshResource;
    class ShaderResource;

    class DataModule : public Module
    {
    public:
        explicit DataModule(const Engine* engine);

        [[nodiscard]] const StandardMaterialResource& GetDefaultMaterial() const;

        TextureResource& CreateTextureResource(const ResourceOrigin& resourceOrigin);
        TextureResource& LoadTextureResource(const std::string& filepath);
        void UnloadTextureResource(TextureResource& textureResource);

        StandardMaterialResource& CreateStandardMaterialResource(const ResourceOrigin& resourceOrigin);
        StandardMaterialResource& DuplicateStandardMaterialResource(const StandardMaterialResource& materialResource);

        ModelResource& CreateModelResource(const ResourceOrigin& resourceOrigin);
        ModelResource& LoadModelResource(const std::string& filepath);
        void UnloadModelResource(ModelResource& modelResource);

        MeshResource& CreateMeshResource(const ResourceOrigin& resourceOrigin);
        void RefreshMeshResource(MeshResource& meshResource, Mesh mesh);
        void UnloadMeshResource(MeshResource& meshResource);

        ShaderResource& CreateShaderResource(const ResourceOrigin& resourceOrigin);
        ShaderResource& LoadShaderResource(const std::string& vertexFilepath, const std::string& fragmentFilepath);
        void UnloadShaderResource(ShaderResource& shaderResource);

    private:
        void Init() override;
        void Dispose() override;

        void AddResource(const std::shared_ptr<Resource>& resource);
        void UnloadResource(Resource& resource);

    private:
        std::map<ResourceType, std::vector<std::shared_ptr<Resource>>> _resources;
        StandardMaterialResource _defaultMaterial;
    };
} // GEngine

#endif //GENGINEGAME_DATAMODULE_H
