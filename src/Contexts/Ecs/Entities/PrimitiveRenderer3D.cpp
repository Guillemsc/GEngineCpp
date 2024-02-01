//
// Created by Guillem on 01/02/2024.
//

#include "PrimitiveRenderer3D.h"

#include "Core/Engine.h"
#include "Contexts/Renderer3D/Modules/Renderer3DModule.h"
#include "raylib.h"

namespace GEngine
{
    PrimitiveRenderer3D::PrimitiveRenderer3D(const Engine *engine) : Entity(engine)
    {
        _tickEvent.Subscribe([this]() { Tick(); });
    }

    void PrimitiveRenderer3D::Tick()
    {
        _engine->GetRenderer3D().lock()->AddToRenderQueue(1, [this]() { Render(); });
    }

    void PrimitiveRenderer3D::Render()
    {
        //Mesh cubeMesh = GenMeshCube(size,size,size);

        DrawCube({0, 0, 0}, 2.0f, 2.0f, 2.0f, BLUE);
    }
} // GEngine