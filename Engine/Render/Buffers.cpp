//
// Created by sunvy on 07/02/2026.
//

#include "Buffers.h"

#include <complex>
#include <glad/glad.h>

namespace
{
    struct ShaderDataTypeInfo
    {
        size_t size = 0;
        int count = 0;
        int type = 0;
    };

    constexpr ShaderDataTypeInfo GetInfo(SunsetEngine::ShaderDataType type)
    {
        switch (type)
        {
            case SunsetEngine::ShaderDataType::Float:
                {
                    return {sizeof(float), 1, GL_FLOAT};
                }
            case SunsetEngine::ShaderDataType::Float2:
                {
                    return {sizeof(float) * 2, 2, GL_FLOAT};
                }
            case SunsetEngine::ShaderDataType::Float3:
                {
                    return {sizeof(float) * 3, 3, GL_FLOAT};
                }
            case SunsetEngine::ShaderDataType::Float4:
                {
                    return {sizeof(float) * 4, 4, GL_FLOAT};
                }
            case SunsetEngine::ShaderDataType::Mat3:
                {
                    return {sizeof(float) * 3 * 3, 3 * 3, GL_FLOAT};
                }
            case SunsetEngine::ShaderDataType::Mat4:
                {
                    return {sizeof(float) * 4 * 4, 4 * 4,GL_FLOAT};
                }
            case SunsetEngine::ShaderDataType::Int:
                {
                    return {sizeof(int), 1, GL_INT};
                }
            case SunsetEngine::ShaderDataType::Int2:
                {
                    return {sizeof(int) * 2, 2, GL_INT};
                }
            case SunsetEngine::ShaderDataType::Int3:
                {
                    return {sizeof(int) * 3, 3, GL_INT};
                }
            case SunsetEngine::ShaderDataType::Int4:
                {
                    return {sizeof(int) * 4, 4, GL_INT};
                }
            case SunsetEngine::ShaderDataType::UInt:
                {
                    return {sizeof(uint32_t), 1, GL_UNSIGNED_INT};
                }
            case SunsetEngine::ShaderDataType::Bool:
                {
                    return {sizeof(bool), 1, GL_BOOL};
                }
        }
    }

    size_t CalculateStride(std::vector<SunsetEngine::BufferElement>& type)
    {
        uint32_t offset = 0;
        size_t stride = 0;

        for (auto& element : type)
        {
            element.offset = offset;
            offset += element.size;
            stride += element.size;
        }

        return stride;
    }
}

namespace SunsetEngine
{
    BufferElement::BufferElement(ShaderDataType type, const std::string_view& name, bool normalized)
        : name(name)
        , type(type)
        , size(GetInfo(type).size)
        , offset(0)
        , normalized(normalized)
    {
    }

    int BufferElement::Count() const
    {
        return GetInfo(type).count;
    }

    int BufferElement::Type() const
    {
        return GetInfo(type).type;
    }
}
