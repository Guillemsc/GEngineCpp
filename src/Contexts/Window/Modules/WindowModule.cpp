//
// Created by Guillem on 01/02/2024.
//

#include "WindowModule.h"

#include "raylib.h"

namespace GEngine
{
    WindowModule::WindowModule(const Engine *engine) : Module(engine)
    {

    }

    void WindowModule::Init()
    {
        const int screenWidth = 800;
        const int screenHeight = 450;

        InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera free");
    }

    bool WindowModule::ShouldTick()
    {
        return !WindowShouldClose();
    }

    void WindowModule::Dispose()
    {
        CloseWindow();
    }
} // GEngine