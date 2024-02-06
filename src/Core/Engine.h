//
// Created by Guillem on 31/01/2024.
//

#ifndef GENGINEGAME_ENGINE_H
#define GENGINEGAME_ENGINE_H

#include <vector>
#include <memory>

namespace GEngine
{
    class Module;
    class WindowModule;
    class Renderer3DModule;
    class EcsModule;
    class DataModule;

    class Engine
    {
    public:
        Engine();

        void Init();
        void Tick();
        bool ShouldTick();
        void Dispose();

        [[nodiscard]] WindowModule& GetWindow() const;
        [[nodiscard]] Renderer3DModule& GetRenderer3D() const;
        [[nodiscard]] DataModule& GetData() const;
        [[nodiscard]] EcsModule& GetEcs() const;

    private:
        std::vector<std::shared_ptr<Module>> _modules;

        std::shared_ptr<WindowModule> _windowModule;
        std::shared_ptr<Renderer3DModule> _renderer3DModule;
        std::shared_ptr<DataModule> _dataModule;
        std::shared_ptr<EcsModule> _ecsModule;
    };
}


#endif //GENGINEGAME_ENGINE_H
