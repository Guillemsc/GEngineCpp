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