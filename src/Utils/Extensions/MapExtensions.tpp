//
// Created by Guillem on 06/02/2024.
//

#include <functional>

template<typename TKey, typename TValue>
std::optional<std::reference_wrapper<const TValue>> GEngine::MapExtensions::GetKey(const std::map<TKey, TValue> &map, TKey key)
{
    auto it = map.find(key);

    if (it == map.end())
    {
        return std::nullopt;
    }

    return std::cref(it->second);
}