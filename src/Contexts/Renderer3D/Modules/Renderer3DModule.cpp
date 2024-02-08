//
// Created by Guillem on 01/02/2024.
//

#include "Renderer3DModule.h"

#include <utility>

#include "raylib.h"

#include "Contexts/Data/Resources/MaterialResource.h"
#include "Contexts/Data/Resources/MeshResource.h"
#include "Contexts/Data/Resources/ShaderResource.h"
#include "raymath.h"
#include "rlgl.h"

namespace GEngine
{
    Renderer3DModule::Renderer3DModule(const Engine* engine) : Module(engine)
    {

    }

    void Renderer3DModule::Init()
    {

    }

    void Renderer3DModule::Tick()
    {
        Render();
    }

    void Renderer3DModule::Dispose()
    {

    }

    void Renderer3DModule::AddToRenderQueue(int priority, std::function<void(const Camera3D& camera)> callback)
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

        ClearBackground(GRAY);

        BeginMode3D(camera);

        _renderQueue.Render(camera);

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

    void Renderer3DModule::DrawMesh(const MeshResource& meshResource, MaterialResource& materialResource, Matrix transform)
    {
        std::optional<Mesh> optionalMeshData = meshResource.GetMesh();

        if(!optionalMeshData.has_value())
        {
            return;
        }

        Mesh meshData = optionalMeshData.value();

        std::optional<std::reference_wrapper<ShaderResource>> optionalShaderResource = materialResource.GetShader();

        if(!optionalShaderResource.has_value())
        {
            return;
        }

        materialResource.Bind();

        materialResource.SendAttributesValuesToShader();

        // Get a copy of current matrices to work with,
        // just in case stereo render is required, and we need to modify them
        // NOTE: At this point the modelview matrix just contains the view matrix (camera)
        // That's because BeginMode3D() sets it and there is no model-drawing function
        // that modifies it, all use rlPushMatrix() and rlPopMatrix()

        // Accumulate several model transformations:
        //    transform: model transformation provided (includes DrawModel() params combined with model.transform)
        //    rlGetMatrixTransform(): rlgl internal transform matrix due to push/pop matrix stack
        Matrix matModel = MatrixMultiply(transform, rlGetMatrixTransform());
        Matrix matView = rlGetMatrixModelview();
        Matrix matModelView = MatrixMultiply(matModel, matView);
        Matrix matProjection = rlGetMatrixProjection();
        Matrix matModelViewProjection = MatrixMultiply(matModelView, matProjection);
        Matrix matNormal = MatrixTranspose(MatrixInvert(matModel));

        materialResource.SendBaseShaderMatrixValue(BaseShaderUniformLocations::VERTEX_MODEL, transform);
        materialResource.SendBaseShaderMatrixValue(BaseShaderUniformLocations::VERTEX_VIEW, matView);
        materialResource.SendBaseShaderMatrixValue(BaseShaderUniformLocations::VERTEX_PROJECTION, matProjection);
        materialResource.SendBaseShaderMatrixValue(BaseShaderUniformLocations::VERTEX_MVP, matModelViewProjection);
        materialResource.SendBaseShaderMatrixValue(BaseShaderUniformLocations::VETEX_NORMAL, matNormal);

        // Try binding vertex array objects (VAO)
        rlEnableVertexArray(meshData.vaoId);

        if (meshData.indices != nullptr)
        {
            rlDrawVertexArrayElements(0, meshData.triangleCount * 3, nullptr);
        }
        else
        {
            rlDrawVertexArray(0, meshData.vertexCount);
        }

        // Disable all possible vertex array objects (or VBOs)
        rlDisableVertexArray();
        rlDisableVertexBuffer();
        rlDisableVertexBufferElement();

        // Restore rlgl internal modelview and projection matrices
        rlSetMatrixModelview(matView);
        rlSetMatrixProjection(matProjection);

        materialResource.Unbind();
    }
} // GEngine