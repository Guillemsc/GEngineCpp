////
//// Created by Guillem on 01/02/2024.
////

#include <stdexcept>

template<typename T>
std::shared_ptr<T> GEngine::EcsModule::Create(EntityType entityType, const std::string& name)
{
    const std::shared_ptr<GEngine::Entity>& entity = Create(entityType, name);

    const std::shared_ptr<T>& derivedEntity = std::dynamic_pointer_cast<T>(entity);

    if (!derivedEntity)
    {
        throw std::runtime_error("Wrong cast creating entity");
    }

    return derivedEntity;
}

template<typename T>
std::vector<std::shared_ptr<T>> GEngine::EcsModule::GetAll() const
{
    std::vector<std::shared_ptr<T>> ret;

    std::vector<std::shared_ptr<Entity>> toCheck;
    toCheck.push_back(_rootEntity);

    while(!toCheck.empty())
    {
        std::shared_ptr<Entity> checking = toCheck.front();

        const std::shared_ptr<T>& derivedEntity = std::dynamic_pointer_cast<T>(checking);

        if (derivedEntity)
        {
            ret.push_back(derivedEntity);
        }

        toCheck.erase(toCheck.begin());

        for (const std::shared_ptr<Entity>& child : checking->_childs)
        {
            toCheck.push_back(child);
        }
    }

    return ret;
}