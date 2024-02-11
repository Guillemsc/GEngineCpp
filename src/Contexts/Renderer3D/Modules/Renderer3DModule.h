//
// Created by Guillem on 01/02/2024.
//

#ifndef GENGINEGAME_RENDERER3DMODULE_H
#define GENGINEGAME_RENDERER3DMODULE_H

#include "Contexts/General/Modules/Module.h"

#include "Contexts/Renderer3D/RenderQueue/RenderQueue3D.h"

struct Camera3D;
struct Matrix;

namespace GEngine
{
    class MeshResource;
    class MaterialResource;

    class Renderer3DModule : public Module
    {
    public:
        explicit Renderer3DModule(const Engine* engine);

        void AddToRenderQueue(int priority, std::function<void(const Camera3D& camera)> callback);
        void DrawMesh(const MeshResource& meshResource, MaterialResource& materialResource, Matrix transform);

    protected:
        void Init() override;
        void Tick() override;
        void Dispose() override;

    private:
        void Render();

    private:
        RenderQueue3D _renderQueue;
    };
} // GEngine

#endif //GENGINEGAME_RENDERER3DMODULE_H
