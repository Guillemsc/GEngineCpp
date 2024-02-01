//
// Created by Guillem on 01/02/2024.
//

#ifndef GENGINEGAME_EVENT_H
#define GENGINEGAME_EVENT_H

#include <iostream>
#include <functional>
#include <utility>
#include <vector>

namespace GEngine
{
    class Event
    {
    public:
        using SubscriptionToken = size_t;
        using Callback = std::function<void()>;

    public:
        SubscriptionToken Subscribe(Callback callback)
        {
            _subscriptions[_nextToken] = std::move(callback);
            return _nextToken++;
        }

        void Unsubscribe(SubscriptionToken token)
        {
            auto it = _subscriptions.find(token);
            if (it != _subscriptions.end()) {
                _subscriptions.erase(it);
            }
        }

        void Trigger()
        {
            for (const auto& kv : _subscriptions)
            {
                kv.second();
            }
        }

        void Clear()
        {
            _subscriptions.clear();
            _nextToken = 0;
        }

    private:
        std::unordered_map<SubscriptionToken, Callback> _subscriptions;
        SubscriptionToken _nextToken = 0;
    };
} // GEngine

#endif //GENGINEGAME_EVENT_H
