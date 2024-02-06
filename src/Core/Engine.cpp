//
// Created by Guillem on 31/01/2024.
//

#include "Engine.h"

#include <memory>
#include "spdlog/spdlog.h"

#include "Contexts/General/Modules/Module.h"
#include "Contexts/Window/Modules/WindowModule.h"
#include "Contexts/Renderer3D/Modules/Renderer3DModule.h"
#include "Contexts/Ecs/Modules/EcsModule.h"
#include "Contexts/Data/Modules/DataModule.h"

namespace GEngine
{
    Engine::Engine()
    {
        _windowModule = std::make_shared<WindowModule>(this);
        _modules.push_back(_windowModule);

        _renderer3DModule = std::make_shared<Renderer3DModule>(this);
        _modules.push_back(_renderer3DModule);

        _dataModule = std::make_shared<DataModule>(this);
        _modules.push_back(_dataModule);

        _ecsModule = std::make_shared<EcsModule>(this);
        _modules.push_back(_ecsModule);
    }

    void Engine::Init()
    {
        spdlog::info("Welcome to spdlog!");

        for (const std::shared_ptr<Module>& module : _modules)
        {
            module->Init();
        }
    }

    void Engine::Tick()
    {
        for (const std::shared_ptr<Module>& module : _modules)
        {
            module->Tick();
        }
    }

    bool Engine::ShouldTick()
    {
        for (const std::shared_ptr<Module>& module : _modules)
        {
            bool continueTicking = module->ShouldTick();

            if(!continueTicking)
            {
                return false;
            }
        }

        return true;
    }

    void Engine::Dispose()
    {
        for (auto it = _modules.rbegin(); it != _modules.rend(); ++it)
        {
            (*it)->Dispose();
        }

        _modules.clear();
    }

    WindowModule& Engine::GetWindow() const
    {
        return *_windowModule;
    }

    Renderer3DModule& Engine::GetRenderer3D() const
    {
        return *_renderer3DModule;
    }

    DataModule &Engine::GetData() const
    {
        return *_dataModule;
    }

    EcsModule& Engine::GetEcs() const
    {
        return *_ecsModule;
    }
}
