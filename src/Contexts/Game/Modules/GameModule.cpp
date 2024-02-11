//
// Created by Guillem on 09/02/2024.
//

#include "GameModule.h"

#include "Contexts/Game/Games/Game.h"

#include "Core/Engine.h"
#include "Contexts/Ecs/Modules/EcsModule.h"

namespace GEngine
{
    GameModule::GameModule(const Engine *engine) : Module(engine)
    {

    }

    void GameModule::RunGame(const std::shared_ptr<Game>& game)
    {
        StopCurrentGame();

        game->_engine = const_cast<GEngine::Engine*>(_engine);;

        _currentGame = game;

        game->Init();
    }

    void GameModule::StopCurrentGame()
    {
        if(!_currentGame.has_value())
        {
            return;
        }

        std::shared_ptr<Game> game = _currentGame.value();
        game->Dispose();

        _currentGame.reset();

        _engine->GetEcs().DisposeAll();
    }

    void GameModule::Tick()
    {
        TickCurrentGame();
    }

    void GameModule::Dispose()
    {
        StopCurrentGame();
    }

    void GameModule::TickCurrentGame()
    {
        if(!_currentGame.has_value())
        {
            return;
        }

        std::shared_ptr<Game> game = _currentGame.value();
        game->Tick();
    }
} // GEngine