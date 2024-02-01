//
// Created by Guillem on 01/02/2024.
//

#ifndef GENGINEGAME_MATHEXTENSIONS_H
#define GENGINEGAME_MATHEXTENSIONS_H

#include "raylib.h"

namespace GEngine
{
    class MathExtensions
    {
    public:
        static float RadiansToDegrees(float radians);
        static float DegreesToRadians(float degrees);
        static Vector3 RadiansToDegrees(Vector3 radians);
        static Vector3 DegreesToRadians(Vector3 radians);
    };
} // GEngine

#endif //GENGINEGAME_MATHEXTENSIONS_H
