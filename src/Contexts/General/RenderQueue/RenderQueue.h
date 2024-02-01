//
// Created by Guillem on 01/02/2024.
//

#ifndef GENGINEGAME_RENDERQUEUE_H
#define GENGINEGAME_RENDERQUEUE_H

#include <functional>
#include <queue>

#include "DrawCall.h"

namespace GEngine
{
    class RenderQueue
    {
    public:
        void Add(const DrawCall& drawCall);
        void Render();

    private:
        std::priority_queue<DrawCall> _drawCalls;
    };
} // GEngine

#endif //GENGINEGAME_RENDERQUEUE_H
