//
// Created by Guillem on 01/02/2024.
//

#ifndef GENGINEGAME_RENDERQUEUE3D_H
#define GENGINEGAME_RENDERQUEUE3D_H

#include <queue>

#include "DrawCall.h"

struct Camera3D;

namespace GEngine
{
    class RenderQueue3D
    {
    public:
        void Add(const DrawCall& drawCall);
        void Render(const Camera3D& camera);

    private:
        std::priority_queue<DrawCall> _drawCalls;
    };
} // GEngine

#endif //GENGINEGAME_RENDERQUEUE3D_H
