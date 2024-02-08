//
// Created by Guillem on 01/02/2024.
//

#include "RenderQueue3D.h"

#include "raylib.h"

namespace GEngine
{
    void RenderQueue3D::Add(const DrawCall& drawCall)
    {
        _drawCalls.push(drawCall);
    }

    void RenderQueue3D::Render(const Camera3D& camera)
    {
        while (!_drawCalls.empty())
        {
            const DrawCall& drawCall = _drawCalls.top();

            drawCall.Draw(camera);

            _drawCalls.pop();
        }
    }
} // GEngine