//
// Created by Guillem on 02/02/2024.
//

#include "MeshRenderer3D.h"

#include "raylib.h"

#include "Core/Engine.h"
#include "Contexts/Renderer3D/Modules/Renderer3DModule.h"

namespace GEngine
{
    GEngine::MeshRenderer3D::MeshRenderer3D(const GEngine::Engine *engine) : Entity3D(engine)
    {
        _tickEvent.Subscribe([this](){ Tick(); });
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

        Model model = _model.value();

        model.transform = GetWorldMatrix();

        for (int i = 0; i < model.meshCount; i++)
        {
            Color colorTint = RED;

            model.materials[model.meshMaterial[i]].maps[MATERIAL_MAP_DIFFUSE].color = colorTint;

            DrawMesh(model.meshes[i], model.materials[model.meshMaterial[i]], model.transform);
        }
    }

    void MeshRenderer3D::SetMesh(const Mesh &mesh)
    {
        _model = LoadModelFromMesh(mesh);
    }

    void MeshRenderer3D::ClearMesh()
    {
        _model.reset();
    }
}
