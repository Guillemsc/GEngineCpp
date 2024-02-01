//
// Created by Guillem on 31/01/2024.
//

#ifndef GENGINEGAME_GENGINEBOOTSTRAP_H
#define GENGINEGAME_GENGINEBOOTSTRAP_H

#include <vector>
#include <memory>

class Module;

namespace GEngine
{
    class GEngineBootstrap
    {
    public:
        void Init();
        void Tick();
        void Dispose();
        bool ShouldTick();

    private:
        std::vector<std::shared_ptr<Module>> _modules;
    };
}


#endif //GENGINEGAME_GENGINEBOOTSTRAP_H
