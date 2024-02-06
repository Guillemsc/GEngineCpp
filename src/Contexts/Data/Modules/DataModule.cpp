//
// Created by Guillem on 06/02/2024.
//

#include "DataModule.h"

#include <memory>

#include "Contexts/Data/Resources/TextureResource.h"
#include "Contexts/Data/Resources/StandardMaterialResource.h"
#include "Contexts/Data/ResourceOrigin/ResourceOrigin.h"
#include "Contexts/Data/ResourceOrigin/FileSystemResourceOrigin.h"
#include "Contexts/Data/ResourceOrigin/InternalResourceOrigin.h"

namespace GEngine
{
    DataModule::DataModule(const Engine *engine) : Module(engine)
    {
        _defaultMaterial.SetAlbedoColor(PINK);
    }

    const StandardMaterialResource &DataModule::GetDefaultMaterial() const
    {
        return _defaultMaterial;
    }

    TextureResource& DataModule::LoadTextureResource(const std::string &filepath)
    {
        FileSystemResourceOrigin origin(filepath);
        std::shared_ptr<TextureResource> textureResource = std::make_shared<TextureResource>(origin);

        Image image = LoadImage(filepath.c_str());

        bool invalid = image.data == nullptr || image.width == 0 || image.height == 0;

        if(!invalid)
        {
            Texture texture = LoadTextureFromImage(image);

            invalid = texture.id < 0;

            if(!invalid)
            {
                textureResource->SetTexture(texture);
            }
        }

        UnloadImage(image);

        AddResource(textureResource);

        return *textureResource;
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

    StandardMaterialResource& DataModule::CreateStandardMaterial()
    {
        InternalResourceOrigin origin;
        std::shared_ptr<StandardMaterialResource> materialResource = std::make_shared<StandardMaterialResource>(origin);

        AddResource(materialResource);

        return *materialResource;
    }

    MeshResource &DataModule::LoadMeshResource(const std::string &filepath)
    {
        //Model model = LoadModel(filepath);

        //return nullptr;
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
        switch(resource.GetResourceType())
        {
            case TEXTURE:
            {
                TextureResource& textureResource = static_cast<TextureResource&>(resource);
                UnloadTextureResource(textureResource);
                break;
            }
            case MATERIAL:
            {
                break;
            }
            case MESH:
            {
                break;
            }
        }
    }
} // GEngine