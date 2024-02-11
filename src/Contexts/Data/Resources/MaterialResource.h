//
// Created by Guillem on 02/02/2024.
//

#ifndef GENGINEGAME_MATERIALRESOURCE_H
#define GENGINEGAME_MATERIALRESOURCE_H

#include "Contexts/Data/Resources/Resource.h"
#include "Contexts/Data/Enums/MaterialResourceType.h"

#include <optional>
#include <memory>
#include <map>

#include "raylib.h"
#include "Contexts/Renderer3D/Enums/BaseShaderUniformLocations.h"
#include "Utils/Events/Event.h"

namespace GEngine
{
    class ShaderResource;

    class MaterialResource : public Resource
    {
        friend class Renderer3DModule;

    public:
        [[nodiscard]] MaterialResourceType GetMaterialType() const;

        void SetShader(ShaderResource& shader);
        [[nodiscard]] std::optional<std::reference_wrapper<ShaderResource>> GetShader() const;

        int GetShaderValuePosition(const std::string& locationName);

        void SetShaderIntValue(const std::string& locationName, int value);
        void SetShaderFloatValue(const std::string& locationName, float value);
        void SetShaderVector3Value(const std::string& locationName, Vector3 value);
        void SetShaderVector4Value(const std::string& locationName, Vector4 value);
        void SetShaderColorValue(const std::string& locationName, Color value);
        void SetShaderMatrixValue(const std::string& locationName, Matrix value);
        void SetShaderTextureValue(const std::string& locationName, Texture value);

        void Bind() const;
        void SendAttributesValuesToShader() const;
        void Unbind() const;

    protected:
        explicit MaterialResource(const Engine* engine, const ResourceOrigin& resourceOrigin, MaterialResourceType materialType);

        int GetBaseShaderValuePosition(BaseShaderUniformLocations defaultLocation);

        void SendShaderVector4Value(int location, Vector4 value);
        void SendShaderMatrixValue(int location, Matrix value);

        void SendBaseShaderVector4Value(BaseShaderUniformLocations location, Vector4 value);
        void SendBaseShaderMatrixValue(BaseShaderUniformLocations location, Matrix value);

        void CopyMaterialTo(MaterialResource& other) const;

    private:
        void ResetValuesFromLocations();

        void SetShaderIntValue(int location, int value);
        void SetShaderFloatValue(int location, float value);
        void SetShaderVector3Value(int location, Vector3 value);
        void SetShaderVector4Value(int location, Vector4 value);
        void SetShaderMatrixValue(int location, Matrix value);
        void SetShaderTextureValue(int location, Texture value);

    private:
        const MaterialResourceType _materialType;

        std::optional<std::reference_wrapper<ShaderResource>> _shader;

        std::map<std::string, int> _locationIntValues;
        std::map<std::string, float> _locationFloatValues;
        std::map<std::string, Vector3> _locationVector3Values;
        std::map<std::string, Vector4> _locationVector4Values;
        std::map<std::string, Matrix> _locationMatrixValues;
        std::map<std::string, Texture> _locationTextureValues;

        std::map<int, int> _intValues;
        std::map<int, float> _floatValues;
        std::map<int, Vector3> _vector3Values;
        std::map<int, Vector4> _vector4Values;
        std::map<int, Matrix> _matrixValues;
        std::map<int, Texture> _textureValues;

        std::map<BaseShaderUniformLocations, int> _baseUniformLocations;
    };

} // GEngine

#endif //GENGINEGAME_MATERIALRESOURCE_H
