//
// Created by Guillem on 01/02/2024.
//

#ifndef GENGINEGAME_DRAWCALL_H
#define GENGINEGAME_DRAWCALL_H

#include <functional>

struct Camera3D;

namespace GEngine
{
    class DrawCall
    {
    public:
        DrawCall(int priority, std::function<void(const Camera3D& camera)> callback);
        void Draw(const Camera3D& camera) const;
        bool operator<(const DrawCall& other) const;

    private:
        int _priority = 0;
        std::function<void(const Camera3D& camera)> _callback;
    };
} // GEngine

#endif //GENGINEGAME_DRAWCALL_H
