//
// Created by Guillem on 01/02/2024.
//

#include "DrawCall.h"

#include <utility>

namespace GEngine
{
    DrawCall::DrawCall(int priority, std::function<void()> callback)
    {
        _priority = priority;
        _callback = std::move(callback);
    }

    void DrawCall::Draw() const
    {
        _callback();
    }

    bool DrawCall::operator<(const DrawCall &other) const
    {
        return _priority < other._priority;
    }
} // GEngine