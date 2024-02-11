//
// Created by Guillem on 01/02/2024.
//

template <typename T>
std::optional<std::shared_ptr<T>> GEngine::Entity::GetFirstParentOfType()
{
    std::optional<std::shared_ptr<Entity>> parent = _parent;

    while(parent.has_value())
    {
        const std::shared_ptr<Entity>& parentValue = parent.value();

        const std::shared_ptr<T>& derivedPtr = std::dynamic_pointer_cast<T>(parentValue);

        if (derivedPtr)
        {
            return derivedPtr;
        }

        parent = parentValue->_parent;
    }

    return std::nullopt;
}