//
// Created by Guillem on 01/02/2024.
//

#include "Entity3D.h"
#include "Utils/Extensions/MathExtensions.h"

namespace GEngine
{
    Entity3D::Entity3D(const Engine* engine, EntityType entityType) : Entity(engine, entityType)
    {

    }

    void Entity3D::SetLocalPosition(Vector3 localPosition)
    {
        bool isSame = Vector3Equals(localPosition, _localPosition);

        if (isSame)
        {
            return;
        }

        _localPosition = localPosition;

        RecalculateLocalMatrix();
        RecalculateChildHirearchyWorldValues();
    }

    void Entity3D::SetWorldPosition(Vector3 worldPosition)
    {
        Vector3 parentWorldPosition = Vector3Zero();

        std::optional<std::shared_ptr<Entity3D>> parent = GetFirstParentOfType<Entity3D>();

        if(parent.has_value())
        {
            parentWorldPosition = parent.value()->_worldPosition;
        }

        Vector3 newLocalPosition = Vector3Subtract(worldPosition, parentWorldPosition);

        SetLocalPosition(newLocalPosition);
    }

    void Entity3D::SetLocalRotation(Quaternion localRotation)
    {
        bool isSame = QuaternionEquals(localRotation, _localRotation);

        if (isSame)
        {
            return;
        }

        _localRotation = localRotation;
        _localRotationRadians = QuaternionToEuler(_localRotation);
        _localRotationDegrees = MathExtensions::RadiansToDegrees(_localRotationRadians);

        RecalculateLocalMatrix();
        RecalculateChildHirearchyWorldValues();
    }

    void Entity3D::SetLocalRotationRadians(Vector3 localRotationRadians)
    {
        bool isSame = Vector3Equals(localRotationRadians, _localRotationRadians);

        if (isSame)
        {
            return;
        }

        _localRotationRadians = localRotationRadians;
        _localRotationDegrees = MathExtensions::RadiansToDegrees(_localRotationRadians);
        _localRotation = QuaternionFromEuler(_localRotationRadians.x, _localRotationRadians.y, _localRotationRadians.z);

        RecalculateLocalMatrix();
        RecalculateChildHirearchyWorldValues();
    }

    void Entity3D::SetLocalRotationDegrees(Vector3 localRotationDegrees)
    {
        bool isSame = Vector3Equals(localRotationDegrees, _localRotationDegrees);

        if (isSame)
        {
            return;
        }

        _localRotationDegrees = localRotationDegrees;
        _localRotationRadians = MathExtensions::DegreesToRadians(_localRotationDegrees);
        _localRotation = QuaternionFromEuler(_localRotationRadians.x, _localRotationRadians.y, _localRotationRadians.z);
    }

    void Entity3D::SetWorldRotation(Quaternion worldRotation)
    {
        Quaternion parentWorldRotation = QuaternionIdentity();

        std::optional<std::shared_ptr<Entity3D>> parent = GetFirstParentOfType<Entity3D>();

        if(parent.has_value())
        {
            parentWorldRotation = parent.value()->_worldRotation;
        }

        Quaternion newLocalRotation = QuaternionMultiply(worldRotation, QuaternionInvert(parentWorldRotation));

        SetLocalRotation(newLocalRotation);
    }

    void Entity3D::SetWorldRotationRadians(Vector3 worldRotationRadians)
    {
        Quaternion worldRotation = QuaternionFromEuler(worldRotationRadians.x, worldRotationRadians.y, worldRotationRadians.z);

        SetWorldRotation(worldRotation);
    }

    void Entity3D::SetWorldRotationDegrees(Vector3 worldRotationDegrees)
    {
        Vector3 worldRotationRadians = MathExtensions::DegreesToRadians(worldRotationDegrees);

        SetWorldRotationRadians(worldRotationRadians);
    }

    void Entity3D::SetLocalScale(Vector3 localScale)
    {
        bool isSame = Vector3Equals(localScale, _localScale);

        if (isSame)
        {
            return;
        }

        _localScale = localScale;

        RecalculateLocalMatrix();
        RecalculateChildHirearchyWorldValues();
    }

    Matrix Entity3D::GetWorldMatrix() const
    {
        return _worldMatrix;
    }

    Vector3 Entity3D::GetWorldPosition() const
    {
        return _worldPosition;
    }

    Vector3 Entity3D::GetWorldRotationRadians() const
    {
        return _worldRotationRadians;
    }

    Vector3 Entity3D::GetWorldScale()
    {
        return _worldScale;
    }

    Vector3 Entity3D::GetWorldForward()
    {
        return Vector3
        {
            2 * (_worldRotation.x * _worldRotation.z + _worldRotation.w * _worldRotation.y),
            2 * (_worldRotation.y * _worldRotation.z - _worldRotation.w * _worldRotation.x),
            1 - 2 * (_worldRotation.x * _worldRotation.x + _worldRotation.y * _worldRotation.y)
        };
    }

    void Entity3D::RecalculateLocalMatrix()
    {
        _localMatrix = MatrixTranslate(_localPosition.x, _localPosition.y, _localPosition.z);
        _localMatrix = MatrixMultiply(_localMatrix, QuaternionToMatrix(_localRotation));
        _localMatrix = MatrixMultiply(_localMatrix, MatrixScale(_localScale.x, _localScale.y, _localScale.z));
    }

    void Entity3D::RecalculateWorldValues()
    {
        bool transformHasChanged = false;

        Vector3 previousWorldPosition = _worldPosition;
        Quaternion previousWorldRotation = _worldRotation;
        Vector3 previousWorldScale = _worldScale;

        Matrix parentMatrix = MatrixIdentity();

        std::optional<std::shared_ptr<Entity3D>> parent = GetFirstParentOfType<Entity3D>();

        if(parent.has_value())
        {
            parentMatrix = parent.value()->_worldMatrix;
        }

        _worldMatrix = MatrixMultiply(_localMatrix, parentMatrix);

        _worldPosition = { _worldMatrix.m12, _worldMatrix.m13, _worldMatrix.m14 };
        _worldRotation = QuaternionFromMatrix(_worldMatrix);
        _worldRotationRadians = QuaternionToEuler(_worldRotation);
        _worldRotationDegrees = MathExtensions::RadiansToDegrees(_worldRotationRadians);
        _worldScale = { _worldMatrix.m0, _worldMatrix.m5, _worldMatrix.m10 };

        if(!Vector3Equals(previousWorldPosition, _worldPosition))
        {
            transformHasChanged = true;
        }

        if(!QuaternionEquals(previousWorldRotation, _worldRotation))
        {
            transformHasChanged = true;
        }

        if(!Vector3Equals(previousWorldScale, _worldScale))
        {
            transformHasChanged = true;
        }
    }

    void Entity3D::RecalculateChildHirearchyWorldValues()
    {
        std::vector<Entity3D*> toCheck;
        toCheck.push_back(this);

        while(!toCheck.empty())
        {
            Entity3D* checking = toCheck.front();
            toCheck.erase(toCheck.begin());

            checking->RecalculateWorldValues();

            for (const std::shared_ptr<Entity>& child : checking->GetChilds())
            {
                const std::shared_ptr<Entity3D>& derivedPtr = std::dynamic_pointer_cast<Entity3D>(child);

                if(derivedPtr)
                {
                    toCheck.push_back(derivedPtr.get());
                }
            }
        }
    }
} // GEngine