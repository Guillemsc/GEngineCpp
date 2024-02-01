//
// Created by Guillem on 31/01/2024.
//

#ifndef GENGINEGAME_MODULE_H
#define GENGINEGAME_MODULE_H

namespace GEngine
{
    class Module
    {
        virtual void Init() {};
        virtual void Tick() {};
        virtual void Dispose() {};
    };

} // GEngineBootstrap

#endif //GENGINEGAME_MODULE_H
