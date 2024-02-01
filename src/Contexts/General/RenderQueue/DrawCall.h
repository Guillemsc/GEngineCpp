//
// Created by Guillem on 01/02/2024.
//

#ifndef GENGINEGAME_DRAWCALL_H
#define GENGINEGAME_DRAWCALL_H

#include <functional>

namespace GEngine
{
    class DrawCall
    {
    public:
        DrawCall(int priority, std::function<void()> callback);
        void Draw() const;
        bool operator<(const DrawCall& other) const;

    private:
        int _priority = 0;
        std::function<void()> _callback;
    };
} // GEngine

#endif //GENGINEGAME_DRAWCALL_H
