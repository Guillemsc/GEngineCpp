//
// Created by Guillem on 07/02/2024.
//

#ifndef GENGINEGAME_LIGHT3D_H
#define GENGINEGAME_LIGHT3D_H

#include "raylib.h"

namespace GEngine
{
    struct Light3D
    {
        int type;
        bool enabled;
        Vector3 position;
        Vector3 target;
        Color color;
        float attenuation;

        int enabledLoc;
        int typeLoc;
        int positionLoc;
        int targetLoc;
        int colorLoc;
        int attenuationLoc;
    };

} // GEngine

#endif //GENGINEGAME_LIGHT3D_H
