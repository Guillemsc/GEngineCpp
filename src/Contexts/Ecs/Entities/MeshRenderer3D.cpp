//
// Created by Guillem on 02/02/2024.
//

#include "MeshRenderer3D.h"

#include "Core/Engine.h"
#include "Contexts/Renderer3D/Modules/Renderer3DModule.h"
#include "Contexts/Ecs/Modules/EcsModule.h"
#include "Contexts/Data/Resources/StandardMaterialResource.h"
#include "Contexts/Data/Modules/DataModule.h"
#include "Contexts/Data/Resources/TextureResource.h"
#include "Contexts/Data/Resources/MeshResource.h"
#include "Contexts/Data/Resources/ShaderResource.h"
#include "DirectionalLight3D.h"

namespace GEngine
{
    GEngine::MeshRenderer3D::MeshRenderer3D(const GEngine::Engine *engine, EntityType entityType)
        : Entity3D(engine, entityType)
    {
        _tickEvent.Subscribe([this](){ Tick(); });
    }

    std::optional<std::reference_wrapper<MeshResource>> MeshRenderer3D::GetMesh() const
    {
        return _mesh;
    }

    void MeshRenderer3D::SetMaterial(MaterialResource &materialResource)
    {
        _material = materialResource;
    }

    std::optional<std::reference_wrapper<MaterialResource>> MeshRenderer3D::GetMaterial() const
    {
        return _material;
    }

    void MeshRenderer3D::SetMeshInternal(MeshResource& meshResource)
    {
        _mesh = meshResource;
    }

    void MeshRenderer3D::ClearMesh()
    {
        _mesh.reset();
    }

    bool MeshRenderer3D::HasMesh() const
    {
        return _mesh.has_value();
    }

    void MeshRenderer3D::Tick()
    {
        _engine->GetRenderer3D().AddToRenderQueue(1, [this](const Camera3D& camera){ Render(camera); });
    }

    void MeshRenderer3D::Render(const Camera3D& camera)
    {
        if(!_mesh.has_value())
        {
            return;
        }

        MeshResource& meshResource = _mesh.value();

        std::optional<Mesh> optionalMesh = meshResource.GetMesh();

        if(!optionalMesh.has_value())
        {
            return;
        }

        StandardMaterialResource defaultMaterial = _engine->GetData().GetDefaultMaterial();

        Matrix transform = GetWorldMatrix();

        MaterialResource* materialResource = &defaultMaterial;

        if(_material.has_value())
        {
            materialResource = &_material->get();
        }

        if (materialResource->GetMaterialType() == MaterialResourceType::STANDARD)
        {
            StandardMaterialResource* standardMaterialResource = (StandardMaterialResource*)materialResource;

            Vector4 ambient = { 0.4f, 0.4f, 0.4f, 1.0f };

            standardMaterialResource->SetShaderVector3Value("viewPos", camera.position);
            standardMaterialResource->SetShaderVector4Value("ambient", ambient);

            std::vector<std::shared_ptr<DirectionalLight3D>> directionalLights = _engine->GetEcs().GetAll<DirectionalLight3D>();

            int lightIndex = 0;
            for (const std::shared_ptr<DirectionalLight3D>& lightPtr : directionalLights)
            {
                DirectionalLight3D& light = *lightPtr;

                Vector3 forward = light.GetWorldZ();

                standardMaterialResource->SetShaderIntValue(TextFormat("lights[%i].type", lightIndex), 0);
                standardMaterialResource->SetShaderVector3Value(TextFormat("lights[%i].direction", lightIndex), forward);
                standardMaterialResource->SetShaderColorValue(TextFormat("lights[%i].color", lightIndex), light.GetColor());

                ++lightIndex;
            }
        }

        _engine->GetRenderer3D().DrawMesh(meshResource, *materialResource, transform);
    }
}
