//
// Created by Guillem on 01/02/2024.
//

#include "MathExtensions.h"

#include <cmath>

namespace GEngine
{
    float MathExtensions::RadiansToDegrees(float radians)
    {
        return radians * (180.0f / (float)M_PI);
    }

    float MathExtensions::DegreesToRadians(float degrees)
    {
        return degrees * ((float)M_PI / 180.0f);
    }

    Vector3 MathExtensions::RadiansToDegrees(Vector3 radians)
    {
        return
        {
                RadiansToDegrees(radians.x),
                RadiansToDegrees(radians.y),
                RadiansToDegrees(radians.z)
        };
    }

    Vector3 MathExtensions::DegreesToRadians(Vector3 radians)
    {
        return
        {
            DegreesToRadians(radians.x),
            DegreesToRadians(radians.y),
            DegreesToRadians(radians.z)
        };
    }
} // GEngine