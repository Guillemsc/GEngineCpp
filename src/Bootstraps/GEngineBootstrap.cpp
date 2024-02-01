//
// Created by Guillem on 31/01/2024.
//

#include "GEngineBootstrap.h"
#include "spdlog/spdlog.h"
#include "raylib.h"

namespace GEngine
{
    void GEngineBootstrap::Init()
    {
        spdlog::info("Welcome to spdlog!");

        InitWindow(800, 450, "raylib [core] example - basic window");
    }

    void GEngineBootstrap::Tick()
    {

    }

    void GEngineBootstrap::Dispose()
    {

    }

    bool GEngineBootstrap::ShouldTick()
    {
        return false;
    }
}
