//
// Created by Guillem on 09/02/2024.
//

#ifndef GENGINEGAME_GAMEMODULE_H
#define GENGINEGAME_GAMEMODULE_H

#include "Contexts/General/Modules/Module.h"

#include <optional>

namespace GEngine
{
    class Game;

    class GameModule : public Module
    {
    public:
        explicit GameModule(const Engine* engine);

        void RunGame(const std::shared_ptr<Game>& game);
        void StopCurrentGame();

    protected:
        void Tick() override;
        void Dispose() override;

    private:
        void TickCurrentGame();

        std::optional<std::shared_ptr<Game>> _currentGame;
    };
} // GEngine

#endif //GENGINEGAME_GAMEMODULE_H
