//
// Created by Guillem on 02/02/2024.
//

#ifndef GENGINEGAME_RESOURCE_H
#define GENGINEGAME_RESOURCE_H

#include "Contexts/Data/ResourceOrigin/ResourceOrigin.h"
#include "Contexts/Data/Enums/ResourceType.h"

namespace GEngine
{
    class Engine;

    class Resource
    {
        friend class DataModule;

    public:
        explicit Resource(const Engine* engine, ResourceType resourceType, const ResourceOrigin& resourceOrigin);

        [[nodiscard]] ResourceType GetResourceType() const;
        [[nodiscard]] ResourceOrigin GetResourceOrigin() const;
        [[nodiscard]] bool GetCanBeUnloaded() const;

    private:
        void SetCanBeUnloaded(bool set);

    protected:
        const Engine* _engine;

    private:
        const ResourceType _resourceType;
        const ResourceOrigin _resourceOrigin;
        bool _canBeUnloaded = true;
    };
} // GEngine

#endif //GENGINEGAME_RESOURCE_H
