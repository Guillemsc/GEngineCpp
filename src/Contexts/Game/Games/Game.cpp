//
// Created by Guillem on 09/02/2024.
//

#include "Game.h"

namespace GEngine
{
    const Engine &Game::GetEngine()
    {
        return *_engine;
    }
} // GEngine