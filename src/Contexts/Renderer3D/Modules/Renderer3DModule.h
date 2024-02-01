//
// Created by Guillem on 01/02/2024.
//

#ifndef GENGINEGAME_RENDERER3DMODULE_H
#define GENGINEGAME_RENDERER3DMODULE_H

#include "Contexts/General/Modules/Module.h"
#include "Contexts/General/RenderQueue/RenderQueue.h"

namespace GEngine
{
    class Renderer3DModule : public Module
    {
    public:
        explicit Renderer3DModule(const Engine* engine);

        void AddToRenderQueue(int priority, std::function<void()> callback);

    protected:
        void Init() override;
        void Tick() override;
        void Dispose() override;

    private:
        void Render();

    private:
        RenderQueue _renderQueue;
    };
} // GEngine

#endif //GENGINEGAME_RENDERER3DMODULE_H
