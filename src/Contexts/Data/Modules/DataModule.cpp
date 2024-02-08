//
// Created by Guillem on 06/02/2024.
//

#include "DataModule.h"

#include <memory>

#include "Contexts/Data/Resources/TextureResource.h"
#include "Contexts/Data/Resources/StandardMaterialResource.h"
#include "Contexts/Data/Resources/ModelResource.h"
#include "Contexts/Data/Resources/MeshResource.h"
#include "Contexts/Data/Resources/ShaderResource.h"
#include "Contexts/Data/ResourceOrigin/FileSystemResourceOrigin.h"
#include "Contexts/Data/ResourceOrigin/InternalResourceOrigin.h"
#include "Contexts/Data/ResourceOrigin/ChildResourceOrigin.h"
#include "Contexts/Data/ResourceOrigin/CopyResourceOrigin.h"
#include "Utils/Extensions/MapExtensions.h"
#include "config.h"

namespace GEngine
{
    DataModule::DataModule(const Engine *engine)
        : Module(engine), _defaultMaterial(StandardMaterialResource(_engine, InternalResourceOrigin()))
    {

    }

    void DataModule::Init()
    {
        _defaultMaterial.SetAlbedoColor(PINK);
    }

    void DataModule::Dispose()
    {
        for (auto& pair : _resources)
        {
            std::vector<std::shared_ptr<Resource>>& resourceVector = pair.second;

            for (const std::shared_ptr<Resource>& resourcePtr : resourceVector)
            {
                UnloadResource(*resourcePtr);
            }
        }

        _resources.clear();
    }

    const StandardMaterialResource &DataModule::GetDefaultMaterial() const
    {
        return _defaultMaterial;
    }

    TextureResource &DataModule::CreateTextureResource(const ResourceOrigin &resourceOrigin)
    {
        std::shared_ptr<TextureResource> textureResource = std::make_shared<TextureResource>(_engine, resourceOrigin);

        AddResource(textureResource);

        return *textureResource;
    }

    TextureResource& DataModule::LoadTextureResource(const std::string &filepath)
    {
        FileSystemResourceOrigin origin(filepath);

        TextureResource& textureResource = CreateTextureResource(origin);

        Image image = LoadImage(filepath.c_str());

        bool invalid = image.data == nullptr || image.width == 0 || image.height == 0;

        if(!invalid)
        {
            Texture texture = LoadTextureFromImage(image);

            invalid = texture.id <= 0;

            if(!invalid)
            {
                textureResource.SetTexture(texture);
            }
        }

        UnloadImage(image);

        return textureResource;
    }

    void DataModule::UnloadTextureResource(TextureResource &textureResource)
    {
        if(!textureResource._texture.has_value())
        {
            return;
        }

        Texture texture = textureResource._texture.value();

        UnloadTexture(texture);

        textureResource._texture.reset();
    }

    StandardMaterialResource& DataModule::CreateStandardMaterialResource(const ResourceOrigin& resourceOrigin)
    {
        std::shared_ptr<StandardMaterialResource> materialResource = std::make_shared<StandardMaterialResource>(_engine, resourceOrigin);

        AddResource(materialResource);

        return *materialResource;
    }

    StandardMaterialResource& DataModule::DuplicateStandardMaterialResource(const StandardMaterialResource &materialResource)
    {
        CopyResourceOrigin origin;

        StandardMaterialResource& copy = CreateStandardMaterialResource(origin);

        materialResource.CopyStandardMaterialTo(copy);

        return copy;
    }

    ModelResource &DataModule::CreateModelResource(const ResourceOrigin &resourceOrigin)
    {
        std::shared_ptr<ModelResource> resource = std::make_shared<ModelResource>(_engine, resourceOrigin);

        AddResource(resource);

        return *resource;
    }

    ModelResource &DataModule::LoadModelResource(const std::string &filepath)
    {
        FileSystemResourceOrigin origin(filepath);

        ModelResource& modelResource = CreateModelResource(origin);

        Model model = LoadModel(filepath.c_str());

        modelResource.SetModel(model);

        ChildResourceOrigin childResourceOrigin(modelResource);

        for (int i = 0; i < model.meshCount; i++)
        {
            Mesh& mesh = model.meshes[i];

            MeshResource& meshResource = CreateMeshResource(childResourceOrigin);
            meshResource.SetCanBeUnloaded(false);
            meshResource.SetMesh(mesh);

            modelResource.AddMesh(meshResource);

            Material& material = model.materials[model.meshMaterial[i]];

            StandardMaterialResource& materialResource = CreateStandardMaterialResource(childResourceOrigin);
            materialResource.SetCanBeUnloaded(false);

            for(int i = 0; i < MAX_MATERIAL_MAPS; ++i)
            {
                MaterialMap& map = material.maps[i];

                switch(i)
                {
                    case MATERIAL_MAP_ALBEDO:
                    {
                        materialResource.SetAlbedoColor(map.color);

                        if(map.texture.id > 0)
                        {
                            TextureResource& textureResource = CreateTextureResource(childResourceOrigin);
                            textureResource.SetTexture(map.texture);

                            materialResource.SetAlbedoTexture(textureResource);
                        }

                        break;
                    }

                    case MATERIAL_MAP_METALNESS:
                    {
                        materialResource.SetMetallnessColor(map.color);

                        if(map.texture.id > 0)
                        {
                            TextureResource& textureResource = CreateTextureResource(childResourceOrigin);
                            textureResource.SetTexture(map.texture);

                            materialResource.SetMetallnessTexture(textureResource);
                        }

                        break;
                    }
                }
            }

            modelResource.AddMaterial(materialResource);
        }

        return modelResource;
    }

    void DataModule::UnloadModelResource(ModelResource& modelResource)
    {
        if(!modelResource._model.has_value())
        {
            return;
        }

        Model& model = modelResource._model.value();

        UnloadModel(model);

        modelResource._model.reset();
    }

    MeshResource &DataModule::CreateMeshResource(const ResourceOrigin &resourceOrigin)
    {
        std::shared_ptr<MeshResource> resource = std::make_shared<MeshResource>(_engine, resourceOrigin);

        AddResource(resource);

        return *resource;
    }

    void DataModule::RefreshMeshResource(MeshResource &meshResource, Mesh mesh)
    {
        UnloadMeshResource(meshResource);

        meshResource._mesh = mesh;
    }

    void DataModule::UnloadMeshResource(MeshResource &meshResource)
    {
        if(!meshResource._mesh.has_value())
        {
            return;
        }

        UnloadMesh(meshResource._mesh.value());

        meshResource._mesh.reset();
    }

    ShaderResource &DataModule::CreateShaderResource(const ResourceOrigin &resourceOrigin)
    {
        std::shared_ptr<ShaderResource> resource = std::make_shared<ShaderResource>(_engine, resourceOrigin);

        AddResource(resource);

        return *resource;
    }

    ShaderResource& DataModule::LoadShaderResource(const std::string& vertexFilepath, const std::string& fragmentFilepath)
    {
        FileSystemResourceOrigin origin(vertexFilepath);

        ShaderResource& shaderResource = CreateShaderResource(origin);

        Shader shader = LoadShader(vertexFilepath.c_str(), fragmentFilepath.c_str());

        if(IsShaderReady(shader))
        {
            shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

            shaderResource.SetShader(shader);
        }

        return shaderResource;
    }

    void DataModule::UnloadShaderResource(ShaderResource &shaderResource)
    {
        if(!shaderResource._shader.has_value())
        {
            return;
        }

        UnloadShader(shaderResource._shader.value());

        shaderResource._shader.reset();
    }

    void DataModule::AddResource(const std::shared_ptr<Resource>& resource)
    {
        ResourceType resourceType = resource->GetResourceType();

        auto it = _resources.find(resourceType);

        if (it == _resources.end())
        {
            _resources.insert(std::make_pair(resourceType, std::vector<std::shared_ptr<Resource>>()));
        }

        _resources[resourceType].push_back(resource);
    }

    void DataModule::UnloadResource(Resource &resource)
    {
        bool canBeUnloaded = resource.GetCanBeUnloaded();

        if(!canBeUnloaded)
        {
            return;
        }

        switch(resource.GetResourceType())
        {
            case MATERIAL:
            {
                // Nothing to do
                break;
            }
            case TEXTURE:
            {
                TextureResource& textureResource = static_cast<TextureResource&>(resource);
                UnloadTextureResource(textureResource);
                break;
            }
            case MESH:
            {
                MeshResource& meshResource = static_cast<MeshResource&>(resource);
                UnloadMeshResource(meshResource);
                break;
            }
            case MODEL:
            {
                ModelResource& modelResource = static_cast<ModelResource&>(resource);
                UnloadModelResource(modelResource);
                break;
            }
            case SHADER:
            {
                ShaderResource& shaderResource = static_cast<ShaderResource&>(resource);
                UnloadShaderResource(shaderResource);
                break;
            }
        }
    }
} // GEngine