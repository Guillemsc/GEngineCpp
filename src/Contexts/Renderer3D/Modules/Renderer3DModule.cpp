//
// Created by Guillem on 01/02/2024.
//

#include "Renderer3DModule.h"

#include <utility>

#include "raylib.h"

namespace GEngine
{
    Renderer3DModule::Renderer3DModule(const Engine* engine) : Module(engine)
    {

    }

    void Renderer3DModule::Init()
    {
        Module::Init();
    }

    void Renderer3DModule::Tick()
    {
        Render();
    }

    void Renderer3DModule::Dispose()
    {
        Module::Dispose();
    }

    void Renderer3DModule::AddToRenderQueue(int priority, std::function<void()> callback)
    {
        _renderQueue.Add(DrawCall(priority, std::move(callback)));
    }

    void Renderer3DModule::Render()
    {
        Camera3D camera = { 0 };
        camera.position = { 10.0f, 10.0f, 10.0f }; // Camera position
        camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
        camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
        camera.fovy = 45.0f;                                // Camera field-of-view Y
        camera.projection = CAMERA_PERSPECTIVE;

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        _renderQueue.Render();

        DrawCubeWires({0, 0, 0}, 2.0f, 2.0f, 2.0f, MAROON);

        DrawGrid(10, 1.0f);

        EndMode3D();

        DrawRectangle( 10, 10, 320, 93, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines( 10, 10, 320, 93, BLUE);

        DrawText("Free camera default controls:", 20, 20, 10, BLACK);
        DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
        DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
        DrawText("- Z to zoom to (0, 0, 0)", 40, 80, 10, DARKGRAY);

        EndDrawing();
    }
} // GEngine