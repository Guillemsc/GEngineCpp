//
// Created by Guillem on 01/02/2024.
//

#include "DrawCall.h"

#include <utility>

#include "raylib.h"

namespace GEngine
{
    DrawCall::DrawCall(int priority, std::function<void(const Camera3D& camera)> callback)
    {
        _priority = priority;
        _callback = std::move(callback);
    }

    void DrawCall::Draw(const Camera3D& camera) const
    {
        _callback(camera);
    }

    bool DrawCall::operator<(const DrawCall &other) const
    {
        return _priority < other._priority;
    }
} // GEngine