//
// Created by Guillem on 01/02/2024.
//

#ifndef GENGINEGAME_WINDOWMODULE_H
#define GENGINEGAME_WINDOWMODULE_H

#include "Contexts/General/Modules/Module.h"

namespace GEngine
{
    class Engine;

    class WindowModule : public Module
    {
    public:
        explicit WindowModule(const Engine* engine);

    protected:
        void Init() override;
        bool ShouldTick() override;
        void Dispose() override;
    };
} // GEngine

#endif //GENGINEGAME_WINDOWMODULE_H
