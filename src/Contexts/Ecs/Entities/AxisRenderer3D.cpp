//
// Created by Guillem on 13/02/2024.
//

#include "AxisRenderer3D.h"

#include "Core/Engine.h"
#include "Contexts/Renderer3D/Modules/Renderer3DModule.h"

namespace GEngine
{
    AxisRenderer3D::AxisRenderer3D(const Engine *engine, EntityType entityType) : Entity3D(engine, entityType)
    {
        _tickEvent.Subscribe([this](){ WhenTick(); });
    }

    void AxisRenderer3D::SetAxisLenght(float lenght)
    {
        _axisLenght = lenght;
    }

    void AxisRenderer3D::WhenTick()
    {
        _engine->GetRenderer3D().AddToRenderQueue(2, [this](const Camera3D& camera){ Render(camera); });
    }

    void AxisRenderer3D::Render(const Camera3D &camera)
    {
        Vector3 x = GetWorldX();
        Vector3 y = GetWorldY();
        Vector3 z = GetWorldZ();

        Vector3 start = GetWorldPosition();
        Vector3 endX = Vector3Add(start, Vector3Multiply(x, {_axisLenght, _axisLenght, _axisLenght}));
        Vector3 endY = Vector3Add(start, Vector3Multiply(y, {_axisLenght, _axisLenght, _axisLenght}));
        Vector3 endZ = Vector3Add(start, Vector3Multiply(z, {_axisLenght, _axisLenght, _axisLenght}));

        DrawLine3D(start, endX, RED);
        DrawLine3D(start, endY, GREEN);
        DrawLine3D(start, endZ, BLUE);
    }
} // GEngine