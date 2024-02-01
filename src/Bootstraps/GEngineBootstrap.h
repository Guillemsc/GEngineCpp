//
// Created by Guillem on 31/01/2024.
//

#ifndef GENGINEGAME_GENGINEBOOTSTRAP_H
#define GENGINEGAME_GENGINEBOOTSTRAP_H

#include <vector>
#include <memory>

#include "Contexts/General/Module.h"
#include "Contexts/Ecs/Modules/EcsModule.h"

class Module;
class EcsModule;

namespace GEngine
{
    class GEngineBootstrap
    {
    public:
        GEngineBootstrap();
        void Init();
        void Tick();
        void Dispose();
        bool ShouldTick();

        [[nodiscard]] std::shared_ptr<EcsModule> GetEcs() const;

    private:
        std::vector<std::shared_ptr<Module>> _modules;
        std::shared_ptr<EcsModule> _ecsModule;
    };
}


#endif //GENGINEGAME_GENGINEBOOTSTRAP_H
