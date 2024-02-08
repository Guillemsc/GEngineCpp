//
// Created by Guillem on 02/02/2024.
//

#include "MaterialResource.h"

#include "Contexts/Data/Resources/ShaderResource.h"
#include "rlgl.h"
#include "Utils/Extensions/MapExtensions.h"

namespace GEngine
{
    MaterialResource::MaterialResource(const Engine* engine, const ResourceOrigin &resourceOrigin, MaterialResourceType materialType)
        : Resource(engine, ResourceType::MATERIAL, resourceOrigin), _materialType(materialType)
    {

    }

    MaterialResourceType MaterialResource::GetMaterialType() const
    {
        return _materialType;
    }

    void MaterialResource::SetShader(ShaderResource &shader)
    {
        _floatValues.clear();
        _vector3Values.clear();
        _vector4Values.clear();
        _matrixValues.clear();
        _textureValues.clear();

        _baseUniformLocations.clear();

        _shader = shader;

        ResetValuesFromLocations();
    }

    std::optional<std::reference_wrapper<ShaderResource>> MaterialResource::GetShader() const
    {
        return _shader;
    }

    int MaterialResource::GetShaderValuePosition(const std::string &locationName)
    {
        if(!_shader.has_value())
        {
            return -1;
        }

        ShaderResource& shaderResource = _shader->get();
        return shaderResource.GetUniformIndex(locationName);
    }

    void MaterialResource::SetShaderFloatValue(const std::string &locationName, float value)
    {
        int locationIndex = GetShaderValuePosition(locationName);
        _locationFloatValues[locationName] = value;
        SetShaderFloatValue(locationIndex, value);
    }

    void MaterialResource::SetShaderVector3Value(const std::string &locationName, Vector3 value)
    {
        int locationIndex = GetShaderValuePosition(locationName);
        _locationVector3Values[locationName] = value;
        SetShaderVector3Value(locationIndex, value);
    }

    void MaterialResource::SetShaderVector4Value(const std::string &locationName, Vector4 value)
    {
        int locationIndex = GetShaderValuePosition(locationName);
        _locationVector4Values[locationName] = value;
        SetShaderVector4Value(locationIndex, value);
    }

    void MaterialResource::SetShaderColorValue(const std::string &locationName, Color value)
    {
        Vector4 vector {(float)value.r / 255, (float)value.g / 255, (float)value.b / 255, (float)value.a / 255};
        SetShaderVector4Value(locationName, vector);
    }

    void MaterialResource::SetShaderMatrixValue(const std::string &locationName, Matrix value)
    {
        int locationIndex = GetShaderValuePosition(locationName);
        _locationMatrixValues[locationName] = value;
        SetShaderMatrixValue(locationIndex, value);
    }

    void MaterialResource::SetShaderTextureValue(const std::string &locationName, Texture value)
    {
        int locationIndex = GetShaderValuePosition(locationName);
        _locationTextureValues[locationName] = value;
        SetShaderTextureValue(locationIndex, value);
    }

    void MaterialResource::Bind() const
    {
        if(!_shader.has_value())
        {
            return;
        }

        ShaderResource& shaderResource = _shader->get();

        std::optional<Shader> optionalShader = shaderResource.GetShader();

        if(!optionalShader.has_value())
        {
            return;
        }

        rlEnableShader(optionalShader->id);
    }

    void MaterialResource::SendAttributesValuesToShader() const
    {
        if(!_shader.has_value())
        {
            return;
        }

        ShaderResource& shaderResource = _shader->get();

        for (auto & floatLocation : _floatValues)
        {
            shaderResource.SetFloatUniform(floatLocation.first, floatLocation.second);
        }

        for (auto & _vector3Location : _vector3Values)
        {
            shaderResource.SetVector3Uniform(_vector3Location.first, _vector3Location.second);
        }

        for (auto & _vector4Location : _vector4Values)
        {
            shaderResource.SetVector4Uniform(_vector4Location.first, _vector4Location.second);
        }

        for (auto & _matrixLocation : _matrixValues)
        {
            shaderResource.SetMatrixUniform(_matrixLocation.first, _matrixLocation.second);
        }

        for (auto & _textureLocation : _textureValues)
        {
            shaderResource.SetTextureUniform(_textureLocation.first, _textureLocation.second);
        }
    }

    void MaterialResource::Unbind() const
    {
        rlDisableShader();
    }

    int MaterialResource::GetBaseShaderValuePosition(BaseShaderUniformLocations defaultLocation)
    {
        std::optional<int> optionalLocation = MapExtensions::GetKey(_baseUniformLocations, defaultLocation);

        if(optionalLocation.has_value())
        {
            return optionalLocation.value();
        }

        const char* locationName = nullptr;

        switch(defaultLocation)
        {
            case VERTEX_MVP:
            {
                locationName = "mvp";
                break;
            }
            case VERTEX_VIEW:
            {
                locationName = "matView";
                break;
            }
            case VERTEX_MODEL:
            {
                locationName = "matModel";
                break;
            }
            case VERTEX_PROJECTION:
            {
                locationName = "matProjection";
                break;
            }
            case VETEX_NORMAL:
            {
                locationName = "matNormal";
                break;
            }
        }

        int location = GetShaderValuePosition(locationName);

        _baseUniformLocations[defaultLocation] = location;

        return location;
    }

    void MaterialResource::SendShaderVector4Value(int location, Vector4 value)
    {
        if(!_shader.has_value())
        {
            return;
        }

        _shader->get().SetVector4Uniform(location, value);
    }

    void MaterialResource::SendShaderMatrixValue(int location, Matrix value)
    {
        if(!_shader.has_value())
        {
            return;
        }

        _shader->get().SetMatrixUniform(location, value);
    }

    void MaterialResource::SendBaseShaderVector4Value(BaseShaderUniformLocations location, Vector4 value)
    {
        int locationIndex = GetBaseShaderValuePosition(location);
        SendShaderVector4Value(locationIndex, value);
    }

    void MaterialResource::SendBaseShaderMatrixValue(BaseShaderUniformLocations location, Matrix value)
    {
        int locationIndex = GetBaseShaderValuePosition(location);
        SendShaderMatrixValue(locationIndex, value);
    }

    void MaterialResource::CopyMaterialTo(MaterialResource &other) const
    {
        other._shader = _shader;
        other._floatValues = _floatValues;
        other._vector3Values = _vector3Values;
        other._vector4Values = _vector4Values;
        other._textureValues = _textureValues;
    }

    void MaterialResource::ResetValuesFromLocations()
    {
        for (auto & floatLocation : _locationFloatValues)
        {
            SetShaderFloatValue(floatLocation.first, floatLocation.second);
        }

        for (auto & _vector3Location : _locationVector3Values)
        {
            SetShaderVector3Value(_vector3Location.first, _vector3Location.second);
        }

        for (auto & _vector4Location : _locationVector4Values)
        {
            SetShaderVector4Value(_vector4Location.first, _vector4Location.second);
        }

        for (auto & _matrixLocation : _locationMatrixValues)
        {
            SetShaderMatrixValue(_matrixLocation.first, _matrixLocation.second);
        }

        for (auto & _textureLocation : _locationTextureValues)
        {
            SetShaderTextureValue(_textureLocation.first, _textureLocation.second);
        }
    }

    void MaterialResource::SetShaderFloatValue(int location, float value)
    {
        _floatValues[location] = value;
    }

    void MaterialResource::SetShaderVector3Value(int location, Vector3 value)
    {
        _vector3Values[location] = value;
    }

    void MaterialResource::SetShaderVector4Value(int location, Vector4 value)
    {
        _vector4Values[location] = value;
    }

    void MaterialResource::SetShaderMatrixValue(int location, Matrix value)
    {
        _matrixValues[location] = value;
    }

    void MaterialResource::SetShaderTextureValue(int location, Texture value)
    {
        _textureValues[location] = value;
    }
} // GEngine