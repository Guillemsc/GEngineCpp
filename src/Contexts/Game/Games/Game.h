//
// Created by Guillem on 09/02/2024.
//

#ifndef GENGINEGAME_GAME_H
#define GENGINEGAME_GAME_H

namespace GEngine
{
    class GameModule;
    class Engine;

    class Game
    {
        friend class GameModule;

    public:
        virtual void Init() {};
        virtual void Tick() {};
        virtual void Dispose() {};

    protected:
        const Engine& GetEngine();

    private:
        Engine* _engine = nullptr;
    };
} // GEngine

#endif //GENGINEGAME_GAME_H
