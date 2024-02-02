//
// Created by Guillem on 01/02/2024.
//

#ifndef GENGINEGAME_ENTITY3D_H
#define GENGINEGAME_ENTITY3D_H

#include "Contexts/Ecs/Entities/Entity.h"

#include "raylib.h"
#include "raymath.h"

namespace GEngine
{
    class Engine;

    class Entity3D : public Entity
    {
    public:
        explicit Entity3D(const Engine* engine);
        void SetLocalPosition(Vector3 localPosition);
        void SetWorldPosition(Vector3 worldPosition);

        void SetLocalRotation(Quaternion localRotation);
        void SetLocalRotationRadians(Vector3 localRotationRadians);
        void SetLocalRotationDegrees(Vector3 localRotationDegrees);
        void SetWorldRotation(Quaternion worldRotation);
        void SetWorldRotationRadians(Vector3 worldRotationRadians);
        void SetWorldRotationDegrees(Vector3 worldRotationDegrees);

        void SetLocalScale(Vector3 localScale);

        Matrix GetWorldMatrix() const;
        Vector3 GetWorldPosition() const;
        Vector3 GetWorldRotationRadians() const;
        Vector3 GetWorldScale();

    private:
        void RecalculateLocalMatrix();
        void RecalculateWorldValues();
        void RecalculateChildHirearchyWorldValues();

    private:
        Matrix _localMatrix = MatrixIdentity();
        Matrix _worldMatrix = MatrixIdentity();

        Vector3 _localPosition = Vector3Zero();
        Quaternion _localRotation = QuaternionIdentity();
        Vector3 _localRotationRadians = Vector3Zero();
        Vector3 _localRotationDegrees = Vector3Zero();
        Vector3 _localScale = Vector3One();

        Vector3 _worldPosition = Vector3Zero();
        Quaternion _worldRotation = QuaternionIdentity();
        Vector3 _worldRotationRadians = Vector3Zero();
        Vector3 _worldRotationDegrees = Vector3Zero();
        Vector3 _worldScale = Vector3One();
    };
} // GEngine

#endif //GENGINEGAME_ENTITY3D_H
