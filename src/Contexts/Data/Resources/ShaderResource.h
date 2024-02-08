//
// Created by Guillem on 07/02/2024.
//

#ifndef GENGINEGAME_SHADERRESOURCE_H
#define GENGINEGAME_SHADERRESOURCE_H

#include "Contexts/Data/Resources/Resource.h"

#include <optional>
#include <string>
#include <map>

#include "raylib.h"

#include "Contexts/Renderer3D/Enums/BaseShaderUniformLocations.h"

namespace GEngine
{
    class ShaderResource : public Resource
    {
        friend class DataModule;

    public:
        explicit ShaderResource(const Engine* engine, const ResourceOrigin& resourceOrigin);

        [[nodiscard]] std::optional<Shader> GetShader() const;

        int GetUniformIndex(const std::string& locationName);

        void SetIntUniform(int locationIndex, int value) const;
        void SetFloatUniform(int locationIndex, float value) const;
        void SetVector3Uniform(int locationIndex, Vector3 value) const;
        void SetVector4Uniform(int locationIndex, Vector4 value);
        void SetMatrixUniform(int locationIndex, Matrix value) const;
        void SetTextureUniform(int locationIndex, Texture value) const;

    private:
        void SetShader(const Shader& shader);

    private:
        std::optional<Shader> _shader;
        std::map<std::string, int> _uniformLocations;
    };
} // GEngine

#endif //GENGINEGAME_SHADERRESOURCE_H
