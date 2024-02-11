//
// Created by Guillem on 08/02/2024.
//

#include "Light3D.h"

namespace GEngine
{
    Light3D::Light3D(const Engine *engine, EntityType entityType) : Entity3D(engine, entityType)
    {

    }

    void Light3D::SetColor(Color color)
    {
        _color = color;
    }

    Color Light3D::GetColor()
    {
        return _color;
    }
} // GEngine