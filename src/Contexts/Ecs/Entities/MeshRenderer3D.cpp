//
// Created by Guillem on 02/02/2024.
//

#include "MeshRenderer3D.h"

#include "raylib.h"

#include "Core/Engine.h"
#include "Contexts/Renderer3D/Modules/Renderer3DModule.h"
#include "Contexts/Data/Resources/StandardMaterialResource.h"
#include "Contexts/Data/Modules/DataModule.h"
#include "Contexts/Data/Resources/TextureResource.h"

namespace GEngine
{
    GEngine::MeshRenderer3D::MeshRenderer3D(const GEngine::Engine *engine) : Entity3D(engine)
    {
        _tickEvent.Subscribe([this](){ Tick(); });
    }

    void MeshRenderer3D::SetMaterial(MaterialResource &materialResource)
    {
        _materialResource = materialResource;
    }

    std::optional<std::reference_wrapper<MaterialResource>> MeshRenderer3D::GetMaterial() const
    {
        return _materialResource;
    }

    void MeshRenderer3D::SetMesh(const Mesh &mesh)
    {
        _model = LoadModelFromMesh(mesh);
    }

    void MeshRenderer3D::ClearMesh()
    {
        _model.reset();
    }

    void MeshRenderer3D::Tick()
    {
        _engine->GetRenderer3D().AddToRenderQueue(1, [this](){ Render(); });
    }

    void MeshRenderer3D::Render()
    {
        if(!_model.has_value())
        {
            return;
        }

        Color albedoColor = WHITE;
        std::optional<Texture> albedoTexture;

        if(!_materialResource.has_value())
        {
            const StandardMaterialResource defaultMaterial = _engine->GetData().GetDefaultMaterial();

            albedoColor = defaultMaterial.GetAlbedoColor();
        }
        else
        {
            MaterialResource& materialResource = _materialResource->get();

            if(materialResource.GetMaterialType() == MaterialResourceType::STANDARD)
            {
                StandardMaterialResource& standardMaterial = static_cast<StandardMaterialResource&>(materialResource);

                albedoColor = standardMaterial.GetAlbedoColor();

                std::optional<std::reference_wrapper<TextureResource>> optionalAlbedoTextureResource = standardMaterial.GetAlbedoTexture();

                if(optionalAlbedoTextureResource.has_value())
                {
                    albedoTexture = optionalAlbedoTextureResource->get().GetTexture();
                }
            }
        }

        Model model = _model.value();

        model.transform = GetWorldMatrix();

        for (int i = 0; i < model.meshCount; i++)
        {
            Mesh& mesh = model.meshes[i];
            Material& material = model.materials[model.meshMaterial[i]];

            material.maps[MATERIAL_MAP_ALBEDO].color = albedoColor;

            if(albedoTexture.has_value())
            {
                material.maps[MATERIAL_MAP_ALBEDO].texture = albedoTexture.value();
            }

            DrawMesh(mesh, material, model.transform);
        }
    }
}
