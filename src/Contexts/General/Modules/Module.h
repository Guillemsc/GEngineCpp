//
// Created by Guillem on 31/01/2024.
//

#ifndef GENGINEGAME_MODULE_H
#define GENGINEGAME_MODULE_H

#include <memory>

namespace GEngine
{
    class Engine;

    class Module
    {
        friend class Engine;

    public:
        explicit Module(const Engine* engine);

    protected:
        virtual void Init() {};
        virtual void Tick() {};
        virtual bool ShouldTick() { return true; };
        virtual void Dispose() {};

    protected:
        const Engine* _engine = nullptr;
    };

} // GEngine

#endif //GENGINEGAME_MODULE_H
