//
// Created by Guillem on 07/02/2024.
//

#include "ShaderResource.h"

#include "Utils/Extensions/MapExtensions.h"
#include "rlgl.h"

namespace GEngine
{
    ShaderResource::ShaderResource(const Engine* engine, const ResourceOrigin &resourceOrigin)
        : Resource(engine, ResourceType::SHADER, resourceOrigin)
    {

    }

    std::optional<Shader> ShaderResource::GetShader() const
    {
        return _shader;
    }

    int ShaderResource::GetUniformIndex(const std::string &locationName)
    {
        if(!_shader.has_value())
        {
            return -1;
        }

        std::optional<int> optionalLocation = MapExtensions::GetKey(_uniformLocations, locationName);

        if(optionalLocation.has_value())
        {
            return optionalLocation.value();
        }

        Shader shader = _shader.value();

        int locationIndex = GetShaderLocation(shader, locationName.c_str());

        _uniformLocations[locationName] = locationIndex;

        return locationIndex;
    }

    void ShaderResource::SetIntUniform(int locationIndex, int value) const
    {
        if(!_shader.has_value())
        {
            return;
        }

        SetShaderValue(_shader.value(), locationIndex, &value, SHADER_UNIFORM_INT);
    }

    void ShaderResource::SetFloatUniform(int locationIndex, float value) const
    {
        if(!_shader.has_value())
        {
            return;
        }

        SetShaderValue(_shader.value(), locationIndex, &value, SHADER_UNIFORM_FLOAT);
    }

    void ShaderResource::SetVector3Uniform(int locationIndex, Vector3 value) const
    {
        if(!_shader.has_value())
        {
            return;
        }

        float valueArray[3] = { value.x, value.y, value.z };
        SetShaderValue(_shader.value(), locationIndex, &valueArray, SHADER_UNIFORM_VEC3);
    }

    void ShaderResource::SetVector4Uniform(int locationIndex, Vector4 value)
    {
        if(!_shader.has_value())
        {
            return;
        }

        float valueArray[4] = { value.x, value.y, value.z, value.w };
        SetShaderValue(_shader.value(), locationIndex, &valueArray, SHADER_UNIFORM_VEC4);
    }

    void ShaderResource::SetMatrixUniform(int locationIndex, Matrix matrix) const
    {
        if(!_shader.has_value())
        {
            return;
        }

        SetShaderValueMatrix(_shader.value(), locationIndex, matrix);
    }

    void ShaderResource::SetTextureUniform(int locationIndex, Texture value) const
    {
        if(!_shader.has_value())
        {
            return;
        }

        SetShaderValueTexture(_shader.value(), locationIndex, value);
    }

    void ShaderResource::SetShader(const Shader &shader)
    {
        _shader = shader;
    }
} // GEngine