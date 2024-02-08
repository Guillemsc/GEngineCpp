//
// Created by Guillem on 06/02/2024.
//

#ifndef GENGINEGAME_MESHRESOURCE_H
#define GENGINEGAME_MESHRESOURCE_H

#include "Contexts/Data/Resources/Resource.h"

#include <optional>

#include "raylib.h"

namespace GEngine
{
    class DataModule;

    class MeshResource : public Resource
    {
        friend class DataModule;

    public:
        explicit MeshResource(const Engine* engine, const ResourceOrigin& resourceOrigin);

        [[nodiscard]] std::optional<Mesh> GetMesh() const;

    private:
        void SetMesh(const Mesh& mesh);

    private:
        std::optional<Mesh> _mesh;
    };
} // Gengine

#endif //GENGINEGAME_MESHRESOURCE_H
