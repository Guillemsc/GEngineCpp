//
// Created by Guillem on 01/02/2024.
//

#include "RenderQueue.h"

namespace GEngine
{
    void RenderQueue::Add(const DrawCall& drawCall)
    {
        _drawCalls.push(drawCall);
    }

    void RenderQueue::Render()
    {
        while (!_drawCalls.empty())
        {
            const DrawCall& drawCall = _drawCalls.top();

            drawCall.Draw();

            _drawCalls.pop();
        }
    }
} // GEngine