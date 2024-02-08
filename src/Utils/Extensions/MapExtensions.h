//
// Created by Guillem on 06/02/2024.
//

#ifndef GENGINEGAME_MAPEXTENSIONS_H
#define GENGINEGAME_MAPEXTENSIONS_H

#include <optional>
#include <map>

namespace GEngine
{
    class MapExtensions
    {
    public:
        template<typename TKey, typename TValue>
        static std::optional<std::reference_wrapper<const TValue>> GetKey(const std::map<TKey, TValue>& map, TKey key);
    };

} // GEngine

#include "Utils/Extensions/MapExtensions.tpp"

#endif //GENGINEGAME_MAPEXTENSIONS_H
