//
// Created by Guillem on 08/02/2024.
//

#ifndef GENGINEGAME_BASESHADERUNIFORMLOCATIONS_H
#define GENGINEGAME_BASESHADERUNIFORMLOCATIONS_H

namespace GEngine
{
    enum BaseShaderUniformLocations
    {
        VERTEX_MVP,                 // uniform mat4 mvp
        VERTEX_MODEL,               // uniform mat4 matModel
        VERTEX_VIEW,                // uniform mat4 matView
        VERTEX_PROJECTION,          // uniform mat4 matProjection
        VETEX_NORMAL,               // uniform mat4 matNormal
    };
} // GEngine

#endif //GENGINEGAME_BASESHADERUNIFORMLOCATIONS_H
